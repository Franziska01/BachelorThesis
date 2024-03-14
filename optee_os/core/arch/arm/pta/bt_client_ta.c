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

#include <tee_internal_api.h>
#include <tee_internal_api_extensions.h>
#include <mm/core_mmu.h>
#include <mm/core_memprot.h>
#include <kernel/pseudo_ta.h>
//mybe not neccessary
#include <string.h>
#include <kernel/tee_time.h>

#include <bt_client_ta.h>

/*
 * Called when the instance of the TA is created. This is the first call in
 * the TA.
 */
/*TEE_Result TA_CreateEntryPoint(void)
{
	DMSG("has been called");

	return TEE_SUCCESS;
}*/

/*
 * Called when the instance of the TA is destroyed if the TA has not
 * crashed or panicked. This is the last call in the TA.
 */
/*void TA_DestroyEntryPoint(void)
{
	DMSG("has been called");
}*/

/*
 * Called when a new session is opened to the TA. *sess_ctx can be updated
 * with a value to be able to identify this session in subsequent calls to the
 * TA. In this function you will normally do the global initialization for the
 * TA.
 */
/*TEE_Result TA_OpenSessionEntryPoint(uint32_t param_types,
		TEE_Param __maybe_unused params[4],
		void __maybe_unused **sess_ctx)
{
	uint32_t exp_param_types = TEE_PARAM_TYPES(TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE);

	DMSG("has been called");

	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;

	
	(void)&params;
	(void)&sess_ctx;

	
	//return tee_success;
}*/

/*
 * Called when a session is closed, sess_ctx hold the value that was
 * assigned by TA_OpenSessionEntryPoint().
 */
/*void TA_CloseSessionEntryPoint(void __maybe_unused *sess_ctx)
{
	(void)&sess_ctx;
	
}*/

static TEE_Result startup(uint32_t param_types,
	TEE_Param params[4])
{
	bool ret;
	uint32_t exp_param_types = TEE_PARAM_TYPES(TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE);

	const unsigned long trusted_flag_connect_phys = MYTEE_TRUSTED_BT_CLIENT_WRITE_FLAG_PHYS;
	uint8_t* trusted_flag_connect_virt;

	ret = core_mmu_add_mapping(MEM_AREA_IO_NSEC, trusted_flag_connect_phys, 0x00001000);
	if(ret!=0x1){
		return TEE_ERROR_BAD_STATE;
	}
	trusted_flag_connect_virt = phys_to_virt (trusted_flag_connect_phys, MEM_AREA_IO_NSEC);
	*trusted_flag_connect_virt =0x0;

	//*(trusted_flag_connect_virt +8 ) = 0x0;

	/*const unsigned long trusted_flag_write_phys = MYTEE_TRUSTED_FB_WRITE_FLAG_PHYS;
	uint8_t* trusted_flag_write_virt;

	ret = core_mmu_add_mapping(MEM_AREA_IO_NSEC, trusted_flag_write_phys, 0x00000008);
	if(ret!=0x1){
		return TEE_ERROR_BAD_STATE;
	}
	trusted_flag_write_virt = phys_to_virt (trusted_flag_write_phys, MEM_AREA_IO_NSEC);
	*trusted_flag_write_virt = 0;*/

	return TEE_SUCCESS;


}


static TEE_Result connect(uint32_t param_types,
	TEE_Param params[4])
{
	uint32_t exp_param_types = TEE_PARAM_TYPES(TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE);
	bool ret;
	DMSG("has been called");

	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;

	/*const unsigned long trusted_flag_connect_phys = MYTEE_TRUSTED_FB_MMAP_FLAG_PHYS;
	uint8_t* trusted_flag_connect_virt;

	ret = core_mmu_add_mapping(MEM_AREA_IO_NSEC, trusted_flag_connect_phys, 0x00001000);
	if(ret!=0x1){
		return TEE_ERROR_BAD_STATE;
	}

	trusted_flag_connect_virt = phys_to_virt (trusted_flag_connect_phys, MEM_AREA_IO_NSEC);
	*trusted_flag_connect_virt = 1;*/
	char dest[18] = "DC:41:A9:39:FE:3F";

	//const unsigned long trusted_dest_phys = MYTEE_TRUSTED_BT_CLIENT_DEST_PHYS;
	//uint32_t* trusted_dest_virt;	

	//core_mmu_add_mapping(MEM_AREA_IO_NSEC, trusted_dest_phys, sizeof(dest));
	//trusted_dest_virt = phys_to_virt (trusted_dest_phys, MEM_AREA_IO_NSEC);
	//*trusted_dest_virt = dest;

	return TEE_SUCCESS;
}

static TEE_Result write(uint32_t param_types,
	TEE_Param params[4])
{
	bool ret;
	uint32_t exp_param_types = TEE_PARAM_TYPES(TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE);

	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;
	// TODO
	// maximallänge message

	const unsigned long trusted_flag_connect_phys = MYTEE_TRUSTED_BT_CLIENT_WRITE_FLAG_PHYS;
	uint8_t* trusted_flag_connect_virt;

	ret = core_mmu_add_mapping(MEM_AREA_IO_NSEC, trusted_flag_connect_phys, 0x00001000);
	if(ret!=0x1){
		return TEE_ERROR_BAD_STATE;
	}
	trusted_flag_connect_virt = phys_to_virt (trusted_flag_connect_phys, MEM_AREA_IO_NSEC);
	*trusted_flag_connect_virt =1;

	//*(trusted_flag_connect_virt +8) = 1;

	/*const unsigned long trusted_flag_write_phys = MYTEE_TRUSTED_FB_WRITE_FLAG_PHYS;
	uint8_t* trusted_flag_write_virt;

	ret = core_mmu_add_mapping(MEM_AREA_IO_NSEC, trusted_flag_write_phys, 0x00000008);
	if(ret!=0x1){
		return TEE_ERROR_BAD_STATE;
	}

	trusted_flag_write_virt = phys_to_virt (trusted_flag_write_phys, MEM_AREA_IO_NSEC);
	*trusted_flag_write_virt = 1;*/

	char msg[13] = "Hello World!";

	//const unsigned long trusted_msg_phys = MYTEE_TRUSTED_BT_CLIENT_MESSAGE_PHYS;
	//uint32_t* trusted_msg_virt;	

	//core_mmu_add_mapping(MEM_AREA_IO_NSEC, trusted_msg_phys, 0x00001000);
	//if(ret!=0x1){
	//	return TEE_ERROR_BAD_STATE;
	//}
	//trusted_msg_virt = phys_to_virt (trusted_msg_phys, MEM_AREA_IO_NSEC);
	//trusted_msg_virt = msg;

	return TEE_SUCCESS;
}

static TEE_Result close(uint32_t param_types,
	TEE_Param params[4])
{
	uint32_t exp_param_types = TEE_PARAM_TYPES(TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE);

	bool ret;
	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;

	const unsigned long trusted_flag_connect_phys = MYTEE_TRUSTED_BT_CLIENT_WRITE_FLAG_PHYS;
	uint8_t* trusted_flag_connect_virt;

	ret = core_mmu_add_mapping(MEM_AREA_IO_NSEC, trusted_flag_connect_phys, 0x000001000);
	if(ret!=0x1){
		return TEE_ERROR_BAD_STATE;
	}

	trusted_flag_connect_virt = phys_to_virt (trusted_flag_connect_phys, MEM_AREA_IO_NSEC);
	*trusted_flag_connect_virt = 0;

	//*(trusted_flag_connect_virt +8) = 0;

	/*const unsigned long trusted_flag_write_phys = MYTEE_TRUSTED_FB_WRITE_FLAG_PHYS;
	uint8_t* trusted_flag_write_virt;

	ret = core_mmu_add_mapping(MEM_AREA_IO_NSEC, trusted_flag_write_phys, 0x00000008);
	if(ret!=0x1){
		return TEE_ERROR_BAD_STATE;
	}

	trusted_flag_write_virt = phys_to_virt (trusted_flag_write_phys, MEM_AREA_IO_NSEC);
	*trusted_flag_write_virt = 0;*/

	

	return TEE_SUCCESS;
}
/*
 * Called when a TA is invoked. sess_ctx hold that value that was
 * assigned by TA_OpenSessionEntryPoint(). The rest of the paramters
 * comes from normal world.
 */
TEE_Result invoke_command(void __maybe_unused *sess_ctx,
			uint32_t cmd_id,
			uint32_t param_types, TEE_Param __maybe_unused params[4])
{
	(void)&sess_ctx; /* Unused parameter */

	switch (cmd_id) {
	case TA_BT_CLIENT_STARTUP:
		return startup (param_types, params);
	case TA_BT_CLIENT_CONNECT:
		return connect(param_types, params);
	case TA_BT_CLIENT_WRITE:
		return write(param_types, params);
	case TA_BT_CLIENT_CLOSE:
		return close(param_types, params);
	default:
		return TEE_ERROR_BAD_PARAMETERS;
	}
}

pseudo_ta_register(.uuid = TA_BT_CLIENT_UUID, .name = "bt_client.pta",
		   .flags = PTA_DEFAULT_FLAGS,
		   .invoke_command_entry_point = invoke_command);
