/*
 * Copyright (c) 2016-2017, Linaro Limited
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
#ifndef TA_BT_CLIENT_H
#define TA_BT_CLIENT_H


/*
 * This UUID is generated with uuidgen
 * the ITU-T UUID generator at http://www.itu.int/ITU-T/asn1/uuid.html
 */
#define TA_BT_CLIENT_UUID \
	{ 0x58984b3d, 0x3991, 0x41fd, \
		{ 0xb9, 0x8c, 0xa8, 0x39, 0x46, 0x3f, 0xed, 0x9b} }

/* The function IDs implemented in this TA */
#define TA_BT_CLIENT_CONNECT		0
#define TA_BT_CLIENT_WRITE		1
#define TA_BT_CLIENT_CLOSE		2
#define TA_BT_CLIENT_STARTUP	3

#define MYTEE_MMIO_CONTEXT_DEVICE_FRAMEBUFFER 0x2

#define MYTEE_TRUSTED_BT_CLIENT_CONNECT_FLAG_PHYS 0x0F10D010
#define MYTEE_TRUSTED_BT_CLIENT_WRITE_FLAG_PHYS 0x0F10D018
#define MYTEE_TRUSTED_BT_CLIENT_DEST_PHYS 0x0F10D020
#define MYTEE_TRUSTED_BT_CLIENT_MESSAGE_PHYS 0x0F10D0B0

#define MYTEE_TRUSTED_FB_MMAP_FLAG_PHYS 0x0F10B000
#define MYTEE_TRUSTED_FB_WRITE_FLAG_PHYS 0x0F10B008
#define MYTEE_TRUSTED_FB_MAIL_BOX_SETTING_COUNT_PHYS 0x0F10D000
#define MYTEE_TRUSTED_FB_WRITE_SECURE_SRC_PHYS 0x0F200000


#endif /*TA_BT_CLIENT_H*/
