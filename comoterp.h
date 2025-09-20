
// Copyright 1992, all rights reserved, AIP, Nico de Vries
// COMOTERP.H

#include <io.h>
#ifndef DOS
#include <limits.h>
#endif

extern struct MODE { // not completed yet
   BYTE fForce;       // forcemode is active
   BYTE bDamageProof; // 0=don't care (keep or use 2) 1=set 2=unset
   BYTE bCompressor;  // 1 2 3 etc
   BYTE fSubDirs;     // subdir mode
   BYTE fASubDirs;    // archive subdir mode
   BYTE fInc;         // incremental mode
   BYTE fSMSkip;      // smart skipping yes/no
   BYTE bAddOpt;      // mode for add to archive
      // 1 smart  D
      // 2 always F
   BYTE bExOverOpt;   // overwrite on extract
      // 1 ask    D
      // 2 always F
      // 3 never
   BYTE bMKDIR;       // create directories
      // 1 ask    D
      // 2 always F
      // 3 never
   BYTE bHid;
      // 1 ask
      // 2 always
      // 3 never
   BYTE bDTT;
   ftime ftDTT;
      // bDTT detects if dynamic time travel is active
      // ftDTT
   BYTE fNoLock;

   BYTE fFreshen;  // $FRE
   BYTE fNoPath;   // $AWP, $EWP
   BYTE fSmart;    // $SMR
   BYTE fPrf;      // $PRF

   BYTE fContains;
   char szContains[50];
   BYTE bExcludeAttr;

   BYTE fArca;

   BYTE bELD;
   ftime ftELD;

   BYTE bEED;
   ftime ftEED;

   BYTE fQuery;
   BYTE fNewer;
   BYTE fNew;
   BYTE fNof;
   BYTE fRab;
   BYTE fBak;
   BYTE fKdt;

   BYTE fGlf;
   char szListFile[260];

   BYTE fVlab;
   char cDrive;
} MODE;

#ifdef DOS
#define MASK_PATH_MAX1 150
#define MASK_PATH_MAX2 200
#else
#define MASK_PATH_MAX1 PATH_MAX
#define MASK_PATH_MAX2 PATH_MAX
#endif

struct MPATH {
   char pcTPath[MASK_PATH_MAX1]; // true path
   VPTR vpMasks;     // select masks
   VPTR vpNext;
};

struct MMASK {
   char pcDestPath[MASK_PATH_MAX1]; // command line defined destination path
   #ifdef DOS
   BYTE pbName[11];    // name mask (? for open)
   #else
   char pcName[PATH_MAX];
   #endif
   BYTE fRevs;         // 0 all revisions; 1 specified revision
   DWORD dwRevision;
   VPTR vpNext;
   BYTE bFlag; // ever used ??
   char pcOrig[MASK_PATH_MAX1];
};

extern VPTR Mpath;
