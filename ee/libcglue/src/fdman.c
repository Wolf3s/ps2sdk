/*
# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# (C)2001, Gustavo Scotti (gustavo@scotti.com)
# (c) 2003 Marcus R. Brown <mrbrown@0xd6.org>
# (c) 2023 Francisco Javier Trujillo Mata <fjtrujy@gmail.com>
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
*/

/**
 * @file
 * fdman.c - Manager for fd.
 */

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include <kernel.h>
#include "fdman.h"

#ifdef F___fdman_sema
int __fdman_sema = -1;
#else
extern int __fdman_sema;
#endif

#ifdef F___descriptor_data_pool
__descriptormap_type  __descriptor_data_pool[__FILENO_MAX];
#else
extern __descriptormap_type  __descriptor_data_pool[__FILENO_MAX];
#endif

#ifdef F___descriptormap
__descriptormap_type *__descriptormap[__FILENO_MAX];
#else
extern __descriptormap_type *__descriptormap[__FILENO_MAX];
#endif


#ifdef F___fdman_init
void __fdman_init()
{
	ee_sema_t sema;

	/* Initialize mutex */
	sema.init_count      = 1;
    sema.max_count       = 1;
    sema.option          = 0;
	__fdman_sema = CreateSema(&sema);
	if (__fdman_sema < 0) {
		abort();
	}

	/* Initialize descriptor data*/
	memset(__descriptor_data_pool, 0, sizeof(__descriptormap_type) *__FILENO_MAX);
	/* Initialize descriptor map*/
	memset(__descriptormap, 0, sizeof(__descriptormap_type*)*__FILENO_MAX);

	// We assume STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO are initialized
	__descriptormap[STDIN_FILENO] = &__descriptor_data_pool[STDIN_FILENO];
	__libcglue_init_stdio(&(__descriptormap[STDIN_FILENO]->info), 0);

	__descriptormap[STDOUT_FILENO] = &__descriptor_data_pool[STDOUT_FILENO];
	__libcglue_init_stdio(&(__descriptormap[STDOUT_FILENO]->info), 1);

	__descriptormap[STDERR_FILENO] = &__descriptor_data_pool[STDERR_FILENO];
	__libcglue_init_stdio(&(__descriptormap[STDERR_FILENO]->info), 1 /* ioman doesn't have 2 (stderr) by default, so just use 1 (stdout) */);
}
#endif

#ifdef F___fdman_deinit
void __fdman_deinit()
{
	if (__fdman_sema > 0) {
		DeleteSema(__fdman_sema);
	}
}
#endif


#ifdef F___fdman_get_new_descriptor
int __fdman_get_new_descriptor()
{
	int i = 0;

	WaitSema(__fdman_sema); /* lock here to make thread safe */
	for (i = 0; i < __FILENO_MAX; i++) {
		if (__descriptormap[i] == NULL) {
			__descriptormap[i] = &__descriptor_data_pool[i];
			__descriptormap[i]->ref_count++;
			SignalSema(__fdman_sema); /* release lock */
			return i;
		}
	}
	SignalSema(__fdman_sema); /* release lock */
		
	errno = ENOMEM;
	return -1;
}
#endif


#ifdef F___fdman_get_dup_descriptor
int __fdman_get_dup_descriptor(int fd)
{
	int i = 0;
	
	if (!__IS_FD_VALID(fd)) {
		errno = EBADF;
		return -1;
	}

	WaitSema(__fdman_sema); /* lock here to make thread safe */
	for (i = 0; i < __FILENO_MAX; i++) {
		if (__descriptormap[i] == NULL) {
			__descriptormap[i] = &__descriptor_data_pool[fd];
			__descriptormap[i]->ref_count++;
			SignalSema(__fdman_sema); /* release lock */
			return i;
		}
	}
	SignalSema(__fdman_sema); /* release lock */
	
	errno = ENOMEM;
	return -1;
}
#endif

#ifdef F___fdman_get_dup_descriptor
int __fdman_get_dup2_descriptor(int fd, int newfd)
{	
	if (!__IS_FD_VALID(fd)) {
		errno = EBADF;
		return -1;
	}

	WaitSema(__fdman_sema); /* lock here to make thread safe */
	__descriptormap[newfd] = &__descriptor_data_pool[fd];
	__descriptormap[newfd]->ref_count++;
	SignalSema(__fdman_sema); /* release lock */
	
	return newfd;
}
#endif

#ifdef F___fdman_release_descriptor
void __fdman_release_descriptor(int fd)
{
	if (!__IS_FD_VALID(fd)) {
		errno = EBADF;
		return;
	}

	__descriptormap[fd]->ref_count--;
	
	if (__descriptormap[fd]->ref_count == 0) {
		memset(__descriptormap[fd], 0, sizeof(__descriptormap_type));
	}
	__descriptormap[fd] = NULL;
}
#endif
