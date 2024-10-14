add_library(pthreadglue)
target_include_directories(pthreadglue PUBLIC ${EE_INC} src/include)
target_sources(pthreadglue PRIVATE src/osal.c src/tls-helper.c)
target_link_libraries(pthreadglue PRIVATE kernel)

compile_multiple(pthreadglue src/osal.c OBJECTS
	___threadInfo.o
	___threadDataKey.o
	___getThreadData.o
	___ps2StubThreadEntry.o
	_pte_osInit.o
	_pte_osTerminate.o
	_pte_osThreadStart.o
	_pte_osThreadDelete.o
	_pte_osThreadExitAndDelete.o
	_pte_osThreadExit.o
	_pte_osThreadWaitForEnd.o
	_pte_osThreadGetHandle.o
	_pte_osThreadGetPriority.o
	_pte_osThreadSetPriority.o
	_pte_osThreadCancel.o
	_pte_osThreadCheckCancel.o
	_pte_osThreadSleep.o
	_pte_osThreadGetMinPriority.o
	_pte_osThreadGetMaxPriority.o
	_pte_osThreadGetDefaultPriority.o
	_pthread_num_processors_np.o
	_pte_osMutexCreate.o
	_pte_osMutexDelete.o
	_pte_osMutexLock.o
	_pte_osMutexTimedLock.o
	_pte_osMutexUnlock.o
	_pte_osSemaphoreCreate.o
	_pte_osSemaphoreDelete.o
	_pte_osSemaphorePost.o
	_pte_osSemaphorePend.o
	_pte_osSemaphoreCancellablePend.o
	_pte_osAtomicExchange.o
	_pte_osAtomicCompareExchange.o
	_pte_osAtomicExchangeAdd.o
	_pte_osAtomicDecrement.o
	_pte_osAtomicIncrement.o
)

compile_multiple(pthreadglue src/tls-helper.c OBJECTS
	___keysUsed.o
	___maxTlsValue.o
	___globalTlsLock.o
	___globalTls.o
	_pteTlsGlobalInit.o
	_pteTlsThreadInit.o
	___pteTlsAlloc.o
	___pteTlsSetValue.o
	___getTlsStructFromThread.o
	_pteTlsFree.o
	_pteTlsThreadDestroy.o
	_pteTlsGlobalDestroy.o
	_pte_osTlsSetValue.o
	_pte_osTlsGetValue.o
	_pte_osTlsAlloc.o
	_pte_osTlsFree.o
)

install(TARGETS pthreadglue)