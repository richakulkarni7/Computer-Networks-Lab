/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _DATETIME_H_RPCGEN
#define _DATETIME_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


#define DATETIME_PROG 0x31234567
#define DATETIME_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define BIN_TIME 1
extern  long * bin_time_1(void *, CLIENT *);
extern  long * bin_time_1_svc(void *, struct svc_req *);
#define STR_DATETIME 2
extern  char ** str_datetime_1(long *, CLIENT *);
extern  char ** str_datetime_1_svc(long *, struct svc_req *);
extern int datetime_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define BIN_TIME 1
extern  long * bin_time_1();
extern  long * bin_time_1_svc();
#define STR_DATETIME 2
extern  char ** str_datetime_1();
extern  char ** str_datetime_1_svc();
extern int datetime_prog_1_freeresult ();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_DATETIME_H_RPCGEN */
