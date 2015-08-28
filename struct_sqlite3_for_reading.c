/*
** Each database connection is an instance of the following structure.
*/
struct sqlite3 {
  sqlite3_vfs *pVfs;            /* OS Interface */
  struct Vdbe *pVdbe;           /* List of active virtual machines */
  CollSeq *pDfltColl;           /* The default collating sequence (BINARY) */
  sqlite3_mutex *mutex;         /* Connection mutex */
  Db *aDb;                      /* All backends */
  int nDb;                      /* Number of backends currently in use */
  int flags;                    /* Miscellaneous flags. See below */
  i64 lastRowid;                /* ROWID of most recent insert (see above) */
  i64 szMmap;                   /* Default mmap_size setting */
  unsigned int openFlags;       /* Flags passed to sqlite3_vfs.xOpen() */
  int errCode;                  /* Most recent error code (SQLITE_*) */
  int errMask;                  /* & result codes with this before returning */
  u16 dbOptFlags;               /* Flags to enable/disable optimizations */
  u8 enc;                       /* Text encoding */
  u8 autoCommit;                /* The auto-commit flag. */
  u8 temp_store;                /* 1: file 2: memory 0: default */
  u8 mallocFailed;              /* True if we have seen a malloc failure */
  u8 dfltLockMode;              /* Default locking-mode for attached dbs */
  signed char nextAutovac;      /* Autovac setting after VACUUM if >=0 */
  u8 suppressErr;               /* Do not issue error messages if true */
  u8 vtabOnConflict;            /* Value to return for s3_vtab_on_conflict() */
  u8 isTransactionSavepoint;    /* True if the outermost savepoint is a TS */
  int nextPagesize;             /* Pagesize after VACUUM if >0 */
  u32 magic;                    /* Magic number for detect library misuse */
  int nChange;                  /* Value returned by sqlite3_changes() */
  int nTotalChange;             /* Value returned by sqlite3_total_changes() */
  int aLimit[SQLITE_N_LIMIT];   /* Limits */
  int nMaxSorterMmap;           /* Maximum size of regions mapped by sorter */
  struct sqlite3InitInfo {      /* Information used during initialization */
    int newTnum;                /* Rootpage of table being initialized */
    u8 iDb;                     /* Which db file is being initialized */
    u8 busy;                    /* TRUE if currently initializing */
    u8 orphanTrigger;           /* Last statement is orphaned TEMP trigger */
    u8 imposterTable;           /* Building an imposter table */
  } init;
  int nVdbeActive;              /* Number of VDBEs currently running */
  int nVdbeRead;                /* Number of active VDBEs that read or write */
  int nVdbeWrite;               /* Number of active VDBEs that read and write */
  int nVdbeExec;                /* Number of nested calls to VdbeExec() */
  int nVDestroy;                /* Number of active OP_VDestroy operations */
  int nExtension;               /* Number of loaded extensions */
  void **aExtension;            /* Array of shared library handles */
  void (*xTrace)(void*,const char*);        /* Trace function */
  void *pTraceArg;                          /* Argument to the trace function */
  void (*xProfile)(void*,const char*,u64);  /* Profiling function */
  void *pProfileArg;                        /* Argument to profile function */
  void *pCommitArg;                 /* Argument to xCommitCallback() */   
  int (*xCommitCallback)(void*);    /* Invoked at every commit. */
  void *pRollbackArg;               /* Argument to xRollbackCallback() */   
  void (*xRollbackCallback)(void*); /* Invoked at every commit. */
  void *pUpdateArg;
  void (*xUpdateCallback)(void*,int, const char*,const char*,sqlite_int64);
#ifndef SQLITE_OMIT_WAL
  int (*xWalCallback)(void *, sqlite3 *, const char *, int);
  void *pWalArg;
#endif
  void(*xCollNeeded)(void*,sqlite3*,int eTextRep,const char*);
  void(*xCollNeeded16)(void*,sqlite3*,int eTextRep,const void*);
  void *pCollNeededArg;
  sqlite3_value *pErr;          /* Most recent error message */
  union {
    volatile int isInterrupted; /* True if sqlite3_interrupt has been called */
    double notUsed1;            /* Spacer */
  } u1;
  Lookaside lookaside;          /* Lookaside malloc configuration */
#ifndef SQLITE_OMIT_AUTHORIZATION
  sqlite3_xauth xAuth;          /* Access authorization function */
  void *pAuthArg;               /* 1st argument to the access auth function */
#endif
#ifndef SQLITE_OMIT_PROGRESS_CALLBACK
  int (*xProgress)(void *);     /* The progress callback */
  void *pProgressArg;           /* Argument to the progress callback */
  unsigned nProgressOps;        /* Number of opcodes for progress callback */
#endif
#ifndef SQLITE_OMIT_VIRTUALTABLE
  int nVTrans;                  /* Allocated size of aVTrans */
  Hash aModule;                 /* populated by sqlite3_create_module() */
  VtabCtx *pVtabCtx;            /* Context for active vtab connect/create */
  VTable **aVTrans;             /* Virtual tables with open transactions */
  VTable *pDisconnect;    /* Disconnect these in next sqlite3_prepare() */
#endif
  FuncDefHash aFunc;            /* Hash table of connection functions */
  Hash aCollSeq;                /* All collating sequences */
  BusyHandler busyHandler;      /* Busy callback */
  Db aDbStatic[2];              /* Static space for the 2 default backends */
  Savepoint *pSavepoint;        /* List of active savepoints */
  int busyTimeout;              /* Busy handler timeout, in msec */
  int nSavepoint;               /* Number of non-transaction savepoints */
  int nStatement;               /* Number of nested statement-transactions  */
  i64 nDeferredCons;            /* Net deferred constraints this transaction. */
  i64 nDeferredImmCons;         /* Net deferred immediate constraints */
  int *pnBytesFreed;            /* If not NULL, increment this in DbFree() */
#ifdef SQLITE_ENABLE_UNLOCK_NOTIFY
  /* The following variables are all protected by the STATIC_MASTER 
  ** mutex, not by sqlite3.mutex. They are used by code in notify.c. 
  **
  ** When X.pUnlockConnection==Y, that means that X is waiting for Y to
  ** unlock so that it can proceed.
  **
  ** When X.pBlockingConnection==Y, that means that something that X tried
  ** tried to do recently failed with an SQLITE_LOCKED error due to locks
  ** held by Y.
  */
  sqlite3 *pBlockingConnection; /* Connection that caused SQLITE_LOCKED */
  sqlite3 *pUnlockConnection;           /* Connection to watch for unlock */
  void *pUnlockArg;                     /* Argument to xUnlockNotify */
  void (*xUnlockNotify)(void **, int);  /* Unlock notify callback */
  sqlite3 *pNextBlocked;        /* Next in list of all blocked connections */
#endif
#ifdef SQLITE_USER_AUTHENTICATION
  sqlite3_userauth auth;        /* User authentication information */
#endif
};
