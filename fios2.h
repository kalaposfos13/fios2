// SPDX-FileCopyrightText: Copyright 2025 shadPS4 Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "types.h"

namespace Fios2 {

constexpr u32 ORBIS_FIOS_PATH_MAX = 1024;

typedef s32 OrbisFiosHandle;
typedef OrbisFiosHandle OrbisFiosFH; // file handle
typedef OrbisFiosHandle OrbisFiosDH; // directory handle
typedef OrbisFiosHandle OrbisFiosOp;

typedef u8 OrbisFiosOpEvent;

typedef enum OrbisFiosOpEvents { Complete = 1, Delete = 2, Start = 3 } OrbisFiosOpEvents;
typedef enum OrbisFiosWhence { Set = 0, Current = 1, End = 2 } SceFiosWhence;

typedef s64 OrbisFiosSize;
typedef s64 OrbisFiosOffset;
typedef s64 OrbisFiosDate;
typedef s64 OrbisFiosTime; // in nanoseconds

typedef OrbisFiosTime OrbisFiosTimeInterval;

typedef struct OrbisFiosStat {
    OrbisFiosOffset fileSize;
    OrbisFiosDate accessDate;
    OrbisFiosDate modificationDate;
    OrbisFiosDate creationDate;
    u32 statFlags;
    u32 reserved;
    s64 uid;
    s64 gid;
    s64 dev;
    s64 ino;
    s64 mode;
} OrbisFiosStat;

typedef struct OrbisFiosDirEntry {
    OrbisFiosOffset fileSize;
    uint32_t statFlags;
    uint16_t nameLength;
    uint16_t fullPathLength;
    uint16_t offsetToName;
    uint16_t reserved[3];
    char fullPath[ORBIS_FIOS_PATH_MAX];
} SceFiosDirEntry;

typedef struct OrbisFiosBuffer {
    void* pPtr;
    u64 length;
} OrbisFiosBuffer;

typedef struct OrbisFiosOpenParams {
    u32 openFlags : 16;
    u32 opFlags : 16;
    u32 reserved;
    OrbisFiosBuffer buffer;
} OrbisFiosOpenParams;

typedef int (*OrbisFiosOpCallback)(void* pContext, OrbisFiosOp op, OrbisFiosOpEvent event, int err);

typedef struct OrbisFiosOpAttr {
    OrbisFiosTime deadline;
    OrbisFiosOpCallback pCallback;
    void* pCallbackContext;
    int32_t priority : 8;
    uint32_t opflags : 24;
    uint32_t userTag;
    void* userPtr;
    void* pReserved;
} OrbisFiosOpAttr;

extern "C" {
void _start() {
    return;
}
u8 sceFiosArchiveGetDecompressorThreadCount();
OrbisFiosOp sceFiosArchiveGetMountBufferSize(const OrbisFiosOpAttr* pAttr, const char* pArchivePath,
                                             const OrbisFiosOpenParams* pOpenParams);
s32 sceFiosArchiveGetMountBufferSizeSync(const OrbisFiosOpAttr* pAttr, const char* pArchivePath,
                                         const OrbisFiosOpenParams* pOpenParams);
OrbisFiosOp sceFiosArchiveMount(const OrbisFiosOpAttr* pAttr, OrbisFiosFH* pOutFH,
                                const char* pArchivePath, const char* pMountPoint,
                                OrbisFiosBuffer mountBuffer,
                                const OrbisFiosOpenParams* pOpenParams);
s32 sceFiosArchiveMountSync(const OrbisFiosOpAttr* pAttr, OrbisFiosFH* pOutFH,
                            const char* pArchivePath, const char* pMountPoint,
                            OrbisFiosBuffer mountBuffer, const OrbisFiosOpenParams* pOpenParams);
OrbisFiosOp sceFiosArchiveMountWithOrder();
s32 sceFiosArchiveMountWithOrderSync();
s32 sceFiosArchiveSetDecompressorThreadCount();
s32 sceFiosArchiveUnmount();
s32 sceFiosArchiveUnmountSync();
s32 sceFiosCacheContainsFileRangeSync();
s32 sceFiosCacheContainsFileSync();
s32 sceFiosCacheFlushFileRangeSync();
s32 sceFiosCacheFlushFileSync();
s32 sceFiosCacheFlushSync();
s32 sceFiosCachePrefetchFH();
s32 sceFiosCachePrefetchFHRange();
s32 sceFiosCachePrefetchFHRangeSync();
s32 sceFiosCachePrefetchFHSync();
s32 sceFiosCachePrefetchFile();
s32 sceFiosCachePrefetchFileRange();
s32 sceFiosCachePrefetchFileRangeSync();
s32 sceFiosCachePrefetchFileSync();
s32 sceFiosCancelAllOps();
s32 sceFiosClearTimeStamps();
s32 sceFiosCloseAllFiles();
OrbisFiosDate sceFiosDateFromComponents(tm* pComponents);
OrbisFiosDate sceFiosDateGetCurrent();
tm* sceFiosDateToComponents(OrbisFiosDate date, tm* pOutComponents);
s32 sceFiosDeallocatePassthruFH();
s32 sceFiosDebugDumpDate();
s32 sceFiosDebugDumpDH();
s32 sceFiosDebugDumpError();
s32 sceFiosDebugDumpFH();
s32 sceFiosDebugDumpOp();
s32 sceFiosDelete();
s32 sceFiosDeleteSync();
s32 sceFiosDHClose(const OrbisFiosOpAttr* pAttr, OrbisFiosDH dh);
s32 sceFiosDHCloseSync(const OrbisFiosOpAttr* pAttr, OrbisFiosDH dh);
s32 sceFiosDHGetPath();
OrbisFiosOp sceFiosDHOpen(const OrbisFiosOpAttr* pAttr, OrbisFiosDH* pOutDH, const char* pPath,
                          OrbisFiosBuffer buf);
s32 sceFiosDHOpenSync(const OrbisFiosOpAttr* pAttr, OrbisFiosDH* pOutDH,
                      const char* pPath, OrbisFiosBuffer buf);
OrbisFiosOp sceFiosDHRead(const OrbisFiosOpAttr* pAttr, OrbisFiosDH dh,
                          OrbisFiosDirEntry* pOutEntry);
s32 sceFiosDHReadSync(const OrbisFiosOpAttr* pAttr, OrbisFiosDH dh,
                      OrbisFiosDirEntry* pOutEntry);
s32 sceFiosDirectoryCreate();
s32 sceFiosDirectoryCreateSync();
s32 sceFiosDirectoryCreateWithMode();
s32 sceFiosDirectoryCreateWithModeSync();
s32 sceFiosDirectoryDelete();
s32 sceFiosDirectoryDeleteSync();
bool sceFiosDirectoryExists();
bool sceFiosDirectoryExistsSync();
s32 sceFiosDLLInitialize();
s32 sceFiosDLLTerminate();
OrbisFiosOp sceFiosExists(const OrbisFiosOpAttr* pAttr, const char* pPath,
                          bool* pOutExists);
bool sceFiosExistsSync(const OrbisFiosOpAttr* pAttr, const char* pPath);
s32 sceFiosFHClose(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh);
s32 sceFiosFHCloseSync(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh);
s32 sceFiosFHGetOpenParams();
const char* sceFiosFHGetPath(OrbisFiosFH fh);
OrbisFiosSize sceFiosFHGetSize(OrbisFiosFH fh);
OrbisFiosOp sceFiosFHOpenWithMode(const OrbisFiosOpAttr* pAttr, OrbisFiosFH* pOutFH,
                                  const char* pPath,
                                  const OrbisFiosOpenParams* pOpenParams,
                                  s32 nativeMode);
s32 sceFiosFHOpenWithModeSync(const OrbisFiosOpAttr* pAttr, OrbisFiosFH* pOutFH,
                              const char* pPath,
                              const OrbisFiosOpenParams* pOpenParams,
                              s32 nativeMode);
OrbisFiosOp sceFiosFHOpen(const OrbisFiosOpAttr* pAttr, OrbisFiosFH* pOutFH,
                          const char* pPath, const OrbisFiosOpenParams* pOpenParams);
s32 sceFiosFHOpenSync(const OrbisFiosOpAttr* pAttr, OrbisFiosFH* pOutFH,
                      const char* pPath, const OrbisFiosOpenParams* pOpenParams);
OrbisFiosOp sceFiosFHPread(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh, void* pBuf,
                           OrbisFiosSize length, OrbisFiosOffset offset);
s32 sceFiosFHPreadSync(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh, void* pBuf,
                       OrbisFiosSize length, OrbisFiosOffset offset);
s32 sceFiosFHPreadv();
s32 sceFiosFHPreadvSync();
s32 sceFiosFHPwrite();
s32 sceFiosFHPwriteSync();
s32 sceFiosFHPwritev();
s32 sceFiosFHPwritevSync();
OrbisFiosOp sceFiosFHRead(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh, void* pBuf, OrbisFiosSize length);
OrbisFiosSize sceFiosFHReadSync(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh, void* pBuf, OrbisFiosSize length);
OrbisFiosOp sceFiosFHReadv(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh, const OrbisFiosBuffer iov[], int iovcnt);
OrbisFiosSize sceFiosFHReadvSync(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh, const OrbisFiosBuffer iov[], int iovcnt);
s32 sceFiosFHSeek(OrbisFiosFH fh, OrbisFiosOffset offset, OrbisFiosWhence whence);
s32 sceFiosFHStat();
s32 sceFiosFHStatSync();
s32 sceFiosFHSync();
s32 sceFiosFHSyncSync();
s32 sceFiosFHTell(OrbisFiosFH fh);
s32 sceFiosFHToFileno();
s32 sceFiosFHTruncate();
s32 sceFiosFHTruncateSync();
s32 sceFiosFHWrite();
s32 sceFiosFHWriteSync();
s32 sceFiosFHWritev();
s32 sceFiosFHWritevSync();
s32 sceFiosFileDelete();
s32 sceFiosFileDeleteSync();
OrbisFiosOp sceFiosFileExists(const OrbisFiosOpAttr* pAttr, const char* pPath);
bool sceFiosFileExistsSync(const OrbisFiosOpAttr* pAttr, const char* pPath);
OrbisFiosOp sceFiosFileGetSize(const OrbisFiosOpAttr* pAttr, const char* pPath);
OrbisFiosSize sceFiosFileGetSizeSync(const OrbisFiosOpAttr* pAttr, const char* pPath);
s32 sceFiosFilenoToFH();
OrbisFiosOp sceFiosFileRead(const OrbisFiosOpAttr* pAttr, const char* pPath, void* pBuf, OrbisFiosSize length, OrbisFiosOffset offset);
OrbisFiosSize sceFiosFileReadSync(const OrbisFiosOpAttr* pAttr, const char* pPath, void* pBuf, OrbisFiosSize length, OrbisFiosOffset offset);
s32 sceFiosFileTruncate();
s32 sceFiosFileTruncateSync();
s32 sceFiosFileWrite();
s32 sceFiosFileWriteSync();
s32 sceFiosGetAllDHs();
s32 sceFiosGetAllFHs();
s32 sceFiosGetAllOps();
s32 sceFiosGetDefaultOpAttr();
s32 sceFiosGetGlobalDefaultOpAttr();
s32 sceFiosGetSuspendCount();
s32 sceFiosGetThreadDefaultOpAttr();
s32 sceFiosInitialize();
s32 sceFiosIOFilterAdd();
s32 sceFiosIOFilterCache();
s32 sceFiosIOFilterGetInfo();
s32 sceFiosIOFilterPsarcDearchiver();
s32 sceFiosIOFilterRemove();
s32 sceFiosIsIdle();
s32 sceFiosIsInitialized();
s32 sceFiosIsSuspended();
bool sceFiosIsValidHandle(OrbisFiosHandle h);
s32 sceFiosOpCancel();
s32 sceFiosOpDelete(OrbisFiosOp op);
OrbisFiosSize sceFiosOpGetActualCount(OrbisFiosOp op);
s32 sceFiosOpGetAttr();
s32 sceFiosOpGetBuffer();
s32 sceFiosOpGetError(OrbisFiosOp op);
s32 sceFiosOpGetOffset();
s32 sceFiosOpGetPath();
OrbisFiosSize sceFiosOpGetRequestCount(OrbisFiosOp op);
s32 sceFiosOpIsCancelled();
bool sceFiosOpIsDone(OrbisFiosOp op);
s32 sceFiosOpReschedule();
s32 sceFiosOpRescheduleWithPriority();
s32 sceFiosOpSetBuffer();
s32 sceFiosOpSyncWait(OrbisFiosOp op);
OrbisFiosSize sceFiosOpSyncWaitForIO(OrbisFiosOp op);
s32 sceFiosOpWait(OrbisFiosOp op);
s32 sceFiosOpWaitUntil();
s32 sceFiosOverlayAdd();
s32 sceFiosOverlayGetInfo();
s32 sceFiosOverlayGetList();
s32 sceFiosOverlayModify();
s32 sceFiosOverlayRemove();
s32 sceFiosOverlayResolveSync();
s32 sceFiosPathcmp();
s32 sceFiosPathncmp();
s32 sceFiosPathNormalize();
s32 sceFiosPrintf();
s32 sceFiosPrintTimeStamps();
s32 sceFiosRename();
s32 sceFiosRenameSync();
s32 sceFiosResolve();
s32 sceFiosResolveSync();
s32 sceFiosResume();
s32 sceFiosSaveTimeStamp();
s32 sceFiosSetGlobalDefaultOpAttr();
s32 sceFiosSetThreadDefaultOpAttr();
s32 sceFiosShutdownAndCancelOps();
OrbisFiosOp sceFiosStat(const OrbisFiosOpAttr* pAttr, const char* pPath, OrbisFiosStat* pOutStatus);
s32 sceFiosStatSync(const OrbisFiosOpAttr* pAttr, const char* pPath, OrbisFiosStat* pOutStatus);
s32 sceFiosSuspend();
s32 sceFiosTerminate();
s32 sceFiosTimeGetCurrent();
OrbisFiosTimeInterval sceFiosTimeIntervalFromNanoseconds(s64 ns);
s32 sceFiosTimeIntervalToNanoseconds(OrbisFiosTime interval);
s32 sceFiosTraceTimestamp();
s32 sceFiosUpdateParameters();
s32 sceFiosVprintf();

}

} // namespace Fios2