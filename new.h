#ifndef NEW_H
#define NEW_H

#include "libc.h"

inline void *operator new (size_t size, void *p) { 
	(void)size;
	return p; 
}

inline void *operator new [] (size_t size, void *p) {
	(void)size;
	return p;
}

inline void *operator new (size_t count) {
	return malloc(count);
}

inline void *operator new [] (size_t count) {
	return malloc(count);	
}

inline void  operator delete (void *, void *) {

};

inline void  operator delete [] (void *, void *) {

};

inline void operator delete (void* ptr) {
    free(ptr);
}

inline void operator delete [] (void* ptr) {
    free(ptr);
}

inline void operator delete (void* ptr, size_t) {
    free(ptr);
}

inline void operator delete [] (void* ptr, size_t) {
    free(ptr);
}


#endif