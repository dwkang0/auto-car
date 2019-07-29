/*
 * printlog.h
 *
 *  Created on: 2019. 7. 28.
 *      Author: dwkang
 */

#ifndef LOG_H_
#define LOG_H_

#include <stdarg.h>
#include <stdio.h>

//#define USELOG

inline void log(const char *format, ...){
#ifdef USELOG
	static char buf[256];

	va_list ipstart;
	va_start(ipstart, format);

	vsprintf(buf, format, ipstart);
	puts(buf);
#endif
}

#endif /* LOG_H_ */
