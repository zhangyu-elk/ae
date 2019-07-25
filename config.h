#ifdef _WIN32
	
#elif __linux__
	
#endif

#ifdef __AE_DEBUG__
	const __ae_loglevel = __AE_DEBUG__;
#else
	const __ae_loglevel = 0;
#endif

/* -version > 4.1.2 */
#if __GNUC__ > 4 || \
	(__GNUC__ == 4 && __GNUC_MINOR__ > 1) || \
	(__GNUC__ == 4 && __GNUC_MINOR__ == 1 && __GNUC_PATCHLEVEL__ > 1)
	
	#define __GCC_ATOMIC 

#endif