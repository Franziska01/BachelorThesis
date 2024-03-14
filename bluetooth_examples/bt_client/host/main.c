/*
 * Copyright (c) 2016, Linaro Limited
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <err.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <bluetooth.h>
#include <rfcomm.h>
#include <unistd.h>

#include <stdlib.h>  
    
#include <fcntl.h>

/* OP-TEE TEE client API (built by optee_client) */
#include <tee_client_api.h>

/* To the the UUID (found the the TA's h-file(s)) */
#include <bt_client_ta.h>
#define MYTEE_IOCTL_REQUEST_UNSHIELD_BT_CLIENT 0x15

void mytee_iocel_request_unshield_bt_client(void){
	int fd;
 
	if ((fd = open("/dev/mytee_mod", O_RDWR)) < 0){
		printf("Cannot open /dev/mytee_mod. Try again later.\n");
	}
 
	if (ioctl(fd, MYTEE_IOCTL_REQUEST_UNSHIELD_BT_CLIENT, NULL)){
		printf("Cannot write there.\n");
	}
 
	if (close(fd) != 0){
		printf("Cannot close.\n");
	}
}

int main(void)
{
	TEEC_Result res;
	TEEC_Context ctx;
	TEEC_Session sess;
	TEEC_Operation op;
	TEEC_Operation op1;
	TEEC_UUID uuid = TA_BT_CLIENT_UUID;
	uint32_t err_origin;

	struct sockaddr_rc addr = { 0 };
    int s, status;
    char dest[18] = "DC:41:A9:39:FE:3F";
	printf("Dest Addr is %s", dest);

	res = TEEC_InitializeContext(NULL, &ctx);
	if (res != TEEC_SUCCESS)
		errx(1, "TEEC_InitializeContext failed with code 0x%x", res);


	res = TEEC_OpenSession(&ctx, &sess, &uuid,
			       TEEC_LOGIN_PUBLIC, NULL, NULL, &err_origin);
	if (res != TEEC_SUCCESS)
		errx(1, "TEEC_Opensession failed with code 0x%x origin 0x%x",
			res, err_origin);

	memset(&op1, 0, sizeof(op1));

	op1.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_NONE,
					 TEEC_NONE, TEEC_NONE);

	printf("Startup");
	res = TEEC_InvokeCommand(&sess, TA_BT_CLIENT_STARTUP, &op1,
				 &err_origin);
	if (res != TEEC_SUCCESS)
		errx(1, "TEEC_InvokeCommand failed with code 0x%x origin 0x%x",
			res, err_origin);
	printf("TA startup  success \n");

	memset(&op, 0, sizeof(op));

	op.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_NONE,
					 TEEC_NONE, TEEC_NONE);

	s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

	if(s <0) perror("uh oh");

	addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba( dest, &addr.rc_bdaddr );

	printf("Conecting");
	res = TEEC_InvokeCommand(&sess, TA_BT_CLIENT_CONNECT, &op,
				 &err_origin);
	if (res != TEEC_SUCCESS)
		errx(1, "TEEC_InvokeCommand failed with code 0x%x origin 0x%x",
			res, err_origin);
	if (res != TEEC_SUCCESS) printf("Fehler connecting");
	usleep(10000);
	status = connect(s, (struct sockaddr *)&addr, sizeof(addr));

	if( status == 0 ) {
		memset(&op, 0, sizeof(op));
		op.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_NONE,
					 TEEC_NONE, TEEC_NONE);

		printf("Writing");
		res = TEEC_InvokeCommand(&sess, TA_BT_CLIENT_WRITE, &op,
					&err_origin);
		if (res != TEEC_SUCCESS)
			errx(1, "TEEC_InvokeCommand failed with code 0x%x origin 0x%x",
				res, err_origin);
		usleep(100000);
        status = write(s, "Testmsg", 7);
		usleep(100000);
    }
    if( status < 0 ) perror("uh oh");

	memset(&op, 0, sizeof(op));
	op.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_NONE,
					 TEEC_NONE, TEEC_NONE);

	mytee_iocel_request_unshield_bt_client();

	printf("Closing");
	res = TEEC_InvokeCommand(&sess, TA_BT_CLIENT_CLOSE, &op,
				 &err_origin);
	if (res != TEEC_SUCCESS)
		errx(1, "TEEC_InvokeCommand failed with code 0x%x origin 0x%x",
			res, err_origin);

    close(s);

	printf("Closed");

	TEEC_CloseSession(&sess);

	TEEC_FinalizeContext(&ctx);

	return 0;
}


