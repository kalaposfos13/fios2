#include <stdio.h>

#include "fios2.h"
#include "types.h"

// SPDX-FileCopyrightText: Copyright 2025 shadPS4 Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>

#include "assert.h"
#include "logging/log.h"
#include "fios2.h"
#include "fios2_error.h"
#include "orbis/_types/kernel.h"
#include "c++/v1/unordered_map"
#include "c++/v1/vector"
#include <orbis/libkernel.h>
// #include "core/libraries/kernel/file_system.h"
// #include "core/tls.h"

namespace Libraries::Fios2 {

std::mutex m;

OrbisFiosOp op_count = 0;

std::unordered_map<OrbisFiosOp, s32> op_return_codes_map{};
std::unordered_map<OrbisFiosOp, OrbisFiosSize> op_io_return_codes_map{};

std::unordered_map<OrbisFiosFH, std::string> fh_path_map;
std::unordered_map<OrbisFiosDH, std::string> dh_path_map;

std::unordered_map<std::string, bool> file_stat_map;

const char* ToApp0(const char* _arc) {
    static thread_local std::string result;
    std::string arc(_arc);
    auto first_slash = arc.find('/');
    if (first_slash == std::string::npos || first_slash == 0) {
        return _arc;
    }
    result = "/app0" + arc.substr(first_slash);
    return result.c_str();
}

void CallFiosCallback(const OrbisFiosOpAttr* pAttr, OrbisFiosOp op, OrbisFiosOpEvent event,
                      s32 err) {
    if (pAttr && pAttr->pCallback) {
        // LOG_INFO(Lib_Fios2, "Calling callback at {}, for op: {}", (void*)pAttr->pCallback, op);
        int ret = pAttr->pCallback(pAttr->pCallbackContext, op, event, err);
        if (ret != 0) {
            LOG_WARNING(Lib_Fios2, "Callback returned {}", ret);
        }
        // LOG_DEBUG(Lib_Fios2, "Callback returned");
        // std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

u8 PS4_SYSV_ABI sceFiosArchiveGetDecompressorThreadCount() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return 1;
}

OrbisFiosOp PS4_SYSV_ABI sceFiosArchiveGetMountBufferSize(const OrbisFiosOpAttr* pAttr,
                                                          const char* pArchivePath,
                                                          const OrbisFiosOpenParams* pOpenParams) {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    // code
    OrbisFiosOp op = ++op_count;
    op_return_codes_map.emplace(op, ORBIS_OK);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ORBIS_OK);
    return op;
}

s32 PS4_SYSV_ABI sceFiosArchiveGetMountBufferSizeSync(const OrbisFiosOpAttr* pAttr,
                                                      const char* pArchivePath,
                                                      const OrbisFiosOpenParams* pOpenParams) {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    OrbisFiosOp op = sceFiosArchiveGetMountBufferSize(pAttr, pArchivePath, pOpenParams);
    return sceFiosOpSyncWait(op);
}

OrbisFiosOp PS4_SYSV_ABI sceFiosArchiveMount(const OrbisFiosOpAttr* pAttr, OrbisFiosFH* pOutFH,
                                             const char* pArchivePath, const char* pMountPoint,
                                             OrbisFiosBuffer mountBuffer,
                                             const OrbisFiosOpenParams* pOpenParams) {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    OrbisFiosOp op = ++op_count;
    op_return_codes_map.emplace(op, ORBIS_OK);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ORBIS_OK);
    return op;
}

s32 PS4_SYSV_ABI sceFiosArchiveMountSync(const OrbisFiosOpAttr* pAttr, OrbisFiosFH* pOutFH,
                                         const char* pArchivePath, const char* pMountPoint,
                                         OrbisFiosBuffer mountBuffer,
                                         const OrbisFiosOpenParams* pOpenParams) {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    OrbisFiosOp op =
        sceFiosArchiveMount(pAttr, pOutFH, pArchivePath, pMountPoint, mountBuffer, pOpenParams);
    return sceFiosOpSyncWait(op);
}

OrbisFiosOp PS4_SYSV_ABI sceFiosArchiveMountWithOrder() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosArchiveMountWithOrderSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosArchiveSetDecompressorThreadCount() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosArchiveUnmount() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosArchiveUnmountSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");

    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosCacheContainsFileRangeSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");

    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosCacheContainsFileSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");

    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosCacheFlushFileRangeSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");

    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosCacheFlushFileSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");

    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosCacheFlushSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");

    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosCachePrefetchFH() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosCachePrefetchFHRange() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosCachePrefetchFHRangeSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosCachePrefetchFHSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");

    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosCachePrefetchFile() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosCachePrefetchFileRange() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosCachePrefetchFileRangeSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosCachePrefetchFileSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosCancelAllOps() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosClearTimeStamps() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosCloseAllFiles() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

OrbisFiosDate PS4_SYSV_ABI sceFiosDateFromComponents(tm* pComponents) {
    LOG_INFO(Lib_Fios2, "called");
    return mktime(pComponents) * 1000000000;
}

OrbisFiosDate PS4_SYSV_ABI sceFiosDateGetCurrent() {
    LOG_INFO(Lib_Fios2, "called");
    return time(nullptr) * 1000000000;
}

tm* PS4_SYSV_ABI sceFiosDateToComponents(OrbisFiosDate date, tm* pOutComponents) {
    LOG_INFO(Lib_Fios2, "called");
    time_t t = date / 1000000000;
    pOutComponents = gmtime(&t);
    return pOutComponents;
}

s32 PS4_SYSV_ABI sceFiosDeallocatePassthruFH() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosDebugDumpDate() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosDebugDumpDH() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosDebugDumpError() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosDebugDumpFH() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosDebugDumpOp() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosDelete() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosDeleteSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosDHClose(const OrbisFiosOpAttr* pAttr, OrbisFiosDH dh) {
    LOG_WARNING(Lib_Fios2, "(STUBBED) called, dh: {}", dh);
    std::scoped_lock l{m};
    s32 ret = sceKernelClose(dh);
    dh_path_map.erase(dh);
    OrbisFiosOp op = ++op_count;
    op_return_codes_map.emplace(op, dh);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ret);
    return op;
}

s32 PS4_SYSV_ABI sceFiosDHCloseSync(const OrbisFiosOpAttr* pAttr, OrbisFiosDH dh) {
    LOG_DEBUG(Lib_Fios2, "(DUMMY) called");
    OrbisFiosOp op = sceFiosDHClose(pAttr, dh);
    return sceFiosOpSyncWait(op);
}

s32 PS4_SYSV_ABI sceFiosDHGetPath() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

OrbisFiosOp PS4_SYSV_ABI sceFiosDHOpen(const OrbisFiosOpAttr* pAttr, OrbisFiosDH* pOutDH,
                                       const char* pPath, OrbisFiosBuffer buf) {
    LOG_WARNING(Lib_Fios2, "(DUMMY) called, path: {}", pPath);
    std::scoped_lock l{m};

    s32 dh = sceKernelOpen(ToApp0(pPath), O_DIRECTORY, 0);
    dh_path_map[dh] = pPath;

    if (pOutDH) {
        *pOutDH = dh;
    }

    OrbisFiosOp op = ++op_count;
    op_return_codes_map.emplace(op, dh);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, dh);
    return op;
}

s32 PS4_SYSV_ABI sceFiosDHOpenSync(const OrbisFiosOpAttr* pAttr, OrbisFiosDH* pOutDH,
                                   const char* pPath, OrbisFiosBuffer buf) {
    LOG_DEBUG(Lib_Fios2, "(DUMMY) called");
    OrbisFiosOp op = sceFiosDHOpen(pAttr, pOutDH, pPath, buf);
    return sceFiosOpSyncWait(op);
}

OrbisFiosOp PS4_SYSV_ABI sceFiosDHRead(const OrbisFiosOpAttr* pAttr, OrbisFiosDH dh,
                                       OrbisFiosDirEntry* pOutEntry) {
    LOG_WARNING(Lib_Fios2, "(DUMMY) called");

    UNREACHABLE_MSG("todo");

    OrbisFiosOp op = ++op_count;
    op_return_codes_map.emplace(op, ORBIS_OK);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ORBIS_OK);
    return op;
}

s32 PS4_SYSV_ABI sceFiosDHReadSync(const OrbisFiosOpAttr* pAttr, OrbisFiosDH dh,
                                   OrbisFiosDirEntry* pOutEntry) {
    LOG_DEBUG(Lib_Fios2, "(DUMMY) called");
    OrbisFiosOp op = sceFiosDHRead(pAttr, dh, pOutEntry);
    return sceFiosOpSyncWait(op);
}

s32 PS4_SYSV_ABI sceFiosDirectoryCreate() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosDirectoryCreateSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosDirectoryCreateWithMode() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosDirectoryCreateWithModeSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosDirectoryDelete() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosDirectoryDeleteSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

bool PS4_SYSV_ABI sceFiosDirectoryExists() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

bool PS4_SYSV_ABI sceFiosDirectoryExistsSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosDLLInitialize() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosDLLTerminate() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

OrbisFiosOp PS4_SYSV_ABI sceFiosExists(const OrbisFiosOpAttr* pAttr, const char* pPath,
                                       bool* pOutExists) {
    OrbisFiosOp op = ++op_count;
    s32 ret;
    {
        std::scoped_lock l{m};
        std::string path_str = std::string(ToApp0(pPath));
        auto cache_it = file_stat_map.find(path_str);
        bool exists;
        if (cache_it == file_stat_map.end()) { // no cache hit
            OrbisKernelStat st;
            file_stat_map[path_str] = sceKernelStat(ToApp0(pPath), &st) == ORBIS_OK;
            cache_it = file_stat_map.find(path_str);
        } else {
            exists = cache_it->second;
        }
        if (pOutExists) {
            *pOutExists = exists;
        }
        ret = exists ? 1 : 0;
        op_return_codes_map.emplace(op, ret);
    }
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ret);
    // LOG_DEBUG(Lib_Fios2, "ret: {}, op: {}", ret, op);
    return op;
}

bool PS4_SYSV_ABI sceFiosExistsSync(const OrbisFiosOpAttr* pAttr, const char* pPath) {
    // LOG_DEBUG(Lib_Fios2, "(DUMMY) called");
    if (pAttr && pAttr->pCallback) {
        LOG_WARNING(Lib_Fios2, "There is a callback to a sync function!");
    }
    OrbisFiosOp op = sceFiosExists(pAttr, pPath, nullptr);
    return static_cast<bool>(sceFiosOpSyncWait(op));
}

s32 PS4_SYSV_ABI sceFiosFHClose(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh) {
    LOG_WARNING(Lib_Fios2, "(DUMMY) called pAttr: {} fh: {}", (void*)pAttr, fh);
    OrbisFiosOp op = ++op_count;
    s32 ret = sceKernelClose(fh);
    op_return_codes_map.emplace(op, ret);
    fh_path_map.erase(fh);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ret);
    return op;
}

s32 PS4_SYSV_ABI sceFiosFHCloseSync(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh) {
    LOG_WARNING(Lib_Fios2, "(DUMMY) called");
    if (pAttr && pAttr->pCallback) {
        LOG_WARNING(Lib_Fios2, "There is a callback to a sync function!");
    }
    OrbisFiosOp op = sceFiosFHClose(pAttr, fh);
    return sceFiosOpSyncWait(op);
}

s32 PS4_SYSV_ABI sceFiosFHGetOpenParams() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

const char* PS4_SYSV_ABI sceFiosFHGetPath(OrbisFiosFH fh) {
    std::scoped_lock l{m};
    LOG_WARNING(Lib_Fios2, "(DUMMY) called");

    auto it = fh_path_map.find(fh);
    if (it != fh_path_map.end()) {
        return it->second.c_str();
    }
    LOG_ERROR(Lib_Fios2, "Invalid FH: {}", fh);
    return nullptr;
}

OrbisFiosSize PS4_SYSV_ABI sceFiosFHGetSize(OrbisFiosFH fh) {
    LOG_WARNING(Lib_Fios2, "(DUMMY) called");
    OrbisKernelStat sb{};
    sceKernelFstat(fh, &sb);
    return sb.st_size;
}

OrbisFiosOp PS4_SYSV_ABI sceFiosFHOpenWithMode(const OrbisFiosOpAttr* pAttr, OrbisFiosFH* pOutFH,
                                               const char* pPath,
                                               const OrbisFiosOpenParams* pOpenParams,
                                               s32 nativeMode) {
    LOG_WARNING(Lib_Fios2, "(DUMMY) called, path: {}", pPath);
    s32 open_params = pOpenParams ? pOpenParams->openFlags : 1;
    u32 open_param = 1;
    if ((open_params & 3) != 2) {
        if ((open_params & 3) == 3) {
            open_param = 2;
        } else {
            open_param = 0;
        }
    }
    u16 uVar2 = open_params << 6 & 0x200;
    u16 mode = 0;
    if (uVar2 != 0) {
        mode = nativeMode == -1 ? 0x1ff : nativeMode;
    }
    s32 fh =
        sceKernelOpen(ToApp0(pPath),
                              (open_params & 0x1000) << 4 | (open_params << 6) & 0x400 |
                                  (open_params << 6) & 0x200 | (open_params << 1) & 8 | open_param,
                              mode);
    fh_path_map[fh] = pPath;

    *pOutFH = fh;

    OrbisFiosOp op = ++op_count;
    s32 ret = std::min(fh, ORBIS_OK);
    {
        std::scoped_lock l{m};
        op_return_codes_map.emplace(op, ret);
    }
    LOG_DEBUG(Lib_Fios2, "ret: {}, op: {}, fh: {}", ret, op, fh);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ret);
    return op;
}

s32 PS4_SYSV_ABI sceFiosFHOpenWithModeSync(const OrbisFiosOpAttr* pAttr, OrbisFiosFH* pOutFH,
                                           const char* pPath,
                                           const OrbisFiosOpenParams* pOpenParams, s32 nativeMode) {
    LOG_DEBUG(Lib_Fios2, "(DUMMY) called");
    if (pAttr && pAttr->pCallback) {
        LOG_WARNING(Lib_Fios2, "There is a callback to a sync function!");
    }
    OrbisFiosOp op = sceFiosFHOpenWithMode(pAttr, pOutFH, pPath, pOpenParams, nativeMode);
    return sceFiosOpSyncWait(op);
}

OrbisFiosOp PS4_SYSV_ABI sceFiosFHOpen(const OrbisFiosOpAttr* pAttr, OrbisFiosFH* pOutFH,
                                       const char* pPath, const OrbisFiosOpenParams* pOpenParams) {
    // LOG_WARNING(Lib_Fios2, "(DUMMY) called");
    return sceFiosFHOpenWithMode(pAttr, pOutFH, pPath, pOpenParams, -1);
}

s32 PS4_SYSV_ABI sceFiosFHOpenSync(const OrbisFiosOpAttr* pAttr, OrbisFiosFH* pOutFH,
                                   const char* pPath, const OrbisFiosOpenParams* pOpenParams) {
    LOG_DEBUG(Lib_Fios2, "(DUMMY) called");
    if (pAttr && pAttr->pCallback) {
        LOG_WARNING(Lib_Fios2, "There is a callback to a sync function!");
    }
    OrbisFiosOp op = sceFiosFHOpen(pAttr, pOutFH, pPath, pOpenParams);
    return sceFiosOpSyncWait(op);
}

OrbisFiosOp PS4_SYSV_ABI sceFiosFHPread(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh, void* pBuf,
                                        OrbisFiosSize length, OrbisFiosOffset offset) {
    std::scoped_lock l{m};
    // LOG_WARNING(Lib_Fios2, "(DUMMY) called, fh: {}, length: {}, offset: {}", fh,
    // length);
    OrbisFiosSize ret = sceKernelPread(fh, pBuf, length, offset);
    OrbisFiosOp op = ++op_count;
    op_io_return_codes_map.emplace(op, ret);
    // LOG_DEBUG(Lib_Fios2, "fh: {}, ret: {}, op: {}", fh, ret, op);
    if (ret != length) {
        LOG_ERROR(Lib_Fios2, "len: {}, ret: {}", length, ret);
    }
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ret);
    return op;
}

s32 PS4_SYSV_ABI sceFiosFHPreadSync(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh, void* pBuf,
                                    OrbisFiosSize length, OrbisFiosOffset offset) {
    // LOG_DEBUG(Lib_Fios2, "(DUMMY) called");
    if (pAttr && pAttr->pCallback) {
        LOG_WARNING(Lib_Fios2, "There is a callback to a sync function!");
    }
    OrbisFiosOp op = sceFiosFHPread(pAttr, fh, pBuf, length, offset);
    return sceFiosOpSyncWaitForIO(op);
}

s32 PS4_SYSV_ABI sceFiosFHPreadv() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosFHPreadvSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosFHPwrite() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosFHPwriteSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosFHPwritev() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosFHPwritevSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

OrbisFiosOp PS4_SYSV_ABI sceFiosFHRead(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh, void* pBuf,
                                       OrbisFiosSize length) {
    std::scoped_lock l{m};
    // LOG_WARNING(Lib_Fios2, "(DUMMY) called, fh: {}, length: {:#x}", fh, (u64)length);
    OrbisFiosSize ret = sceKernelRead(fh, pBuf, length);
    OrbisFiosOp op = ++op_count;
    if (ret != length) {
        LOG_ERROR(Lib_Fios2, "len: {}, ret: {}", length, ret);
    }
    op_io_return_codes_map.emplace(op, ret);
    // LOG_DEBUG(Lib_Fios2, "ret: {}, op: {}", ret, op);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ret);
    return op;
}

OrbisFiosSize PS4_SYSV_ABI sceFiosFHReadSync(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh,
                                             void* pBuf, OrbisFiosSize length) {
    // LOG_DEBUG(Lib_Fios2, "(DUMMY) called");
    if (pAttr && pAttr->pCallback) {
        LOG_WARNING(Lib_Fios2, "There is a callback to a sync function!");
    }
    OrbisFiosOp op = sceFiosFHRead(pAttr, fh, pBuf, length);
    return sceFiosOpSyncWaitForIO(op);
}

OrbisFiosOp PS4_SYSV_ABI sceFiosFHReadv(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh,
                                        const OrbisFiosBuffer iov[], int iovcnt) {
    std::scoped_lock l{m};
    LOG_WARNING(Lib_Fios2, "(DUMMY) called");

    std::vector<OrbisKernelIovec> kernel_iov(iovcnt);
    for (int i = 0; i < iovcnt; ++i) {
        kernel_iov[i].base = iov[i].pPtr;
        kernel_iov[i].len = static_cast<std::size_t>(iov[i].length);
    }

    s64 ret = sceKernelPreadv(fh, kernel_iov.data(), iovcnt, 0);

    OrbisFiosOp op = ++op_count;
    op_io_return_codes_map.emplace(op, ret);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ret);
    return op;
}

OrbisFiosSize PS4_SYSV_ABI sceFiosFHReadvSync(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh,
                                              const OrbisFiosBuffer iov[], int iovcnt) {
    LOG_DEBUG(Lib_Fios2, "(DUMMY) called");
    if (pAttr && pAttr->pCallback) {
        LOG_WARNING(Lib_Fios2, "There is a callback to a sync function!");
    }
    OrbisFiosOp op = sceFiosFHReadv(pAttr, fh, iov, iovcnt);
    return sceFiosOpSyncWaitForIO(op);
}

s32 PS4_SYSV_ABI sceFiosFHSeek(OrbisFiosFH fh, OrbisFiosOffset offset, OrbisFiosWhence whence) {
    LOG_WARNING(Lib_Fios2, "(DUMMY) called");
    return sceKernelLseek(fh, offset, whence);
}

s32 PS4_SYSV_ABI sceFiosFHStat() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosFHStatSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosFHSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosFHSyncSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosFHTell(OrbisFiosFH fh) {
    LOG_WARNING(Lib_Fios2, "(DUMMY) called");
    return sceKernelLseek(fh, 0, SceFiosWhence::Current);
}

s32 PS4_SYSV_ABI sceFiosFHToFileno() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosFHTruncate() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosFHTruncateSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosFHWrite() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosFHWriteSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosFHWritev() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosFHWritevSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosFileDelete() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosFileDeleteSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

OrbisFiosOp PS4_SYSV_ABI sceFiosFileExists(const OrbisFiosOpAttr* pAttr, const char* pPath) {
    // LOG_WARNING(Lib_Fios2, "(DUMMY) called");
    return sceFiosExists(pAttr, pPath, nullptr);
}

bool PS4_SYSV_ABI sceFiosFileExistsSync(const OrbisFiosOpAttr* pAttr, const char* pPath) {
    // LOG_DEBUG(Lib_Fios2, "(DUMMY) called");
    if (pAttr && pAttr->pCallback) {
        LOG_WARNING(Lib_Fios2, "There is a callback to a sync function!");
    }
    OrbisFiosOp op = sceFiosFileExists(pAttr, pPath);
    return sceFiosOpSyncWaitForIO(op);
}

OrbisFiosOp PS4_SYSV_ABI sceFiosFileGetSize(const OrbisFiosOpAttr* pAttr, const char* pPath) {
    std::scoped_lock l{m};
    OrbisFiosOp op = ++op_count;
    OrbisKernelStat stat{};
    if (sceKernelStat(ToApp0(pPath), &stat) < 0) {
        op_io_return_codes_map.emplace(op, ORBIS_FIOS_ERROR_BAD_PATH);
        return op;
    }
    LOG_WARNING(Lib_Fios2, "(DUMMY) called pAttr: {} path: {} size: {}, op: {}", (void*)pAttr,
                pPath, stat.st_size, op);
    op_io_return_codes_map.emplace(op, stat.st_size);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, static_cast<s32>(stat.st_size));
    return op;
}

OrbisFiosSize PS4_SYSV_ABI sceFiosFileGetSizeSync(const OrbisFiosOpAttr* pAttr, const char* pPath) {
    LOG_DEBUG(Lib_Fios2, "(DUMMY) called");
    OrbisFiosOp op = sceFiosFileGetSize(pAttr, pPath);
    return sceFiosOpSyncWaitForIO(op);
}

s32 PS4_SYSV_ABI sceFiosFilenoToFH() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

OrbisFiosOp PS4_SYSV_ABI sceFiosFileRead(const OrbisFiosOpAttr* pAttr, const char* pPath,
                                         void* pBuf, OrbisFiosSize length, OrbisFiosOffset offset) {
    LOG_WARNING(Lib_Fios2, "(DUMMY) called, path: {}, length: {}, offset: {}", pPath, length,
                offset);

    std::scoped_lock l{m};
    OrbisFiosOp op = ++op_count;
    s64 ret = -1;

    s32 fd = sceKernelOpen(ToApp0(pPath), O_RDONLY, 0);

    if (fd >= 0) {
        ret = sceKernelPread(fd, pBuf, length, offset);
        ret = std::min(ret, (s64)0);
        sceKernelClose(fd);
    }

    op_io_return_codes_map.emplace(op, ret >= 0 ? ret : ORBIS_FIOS_ERROR_BAD_PATH);
    if (ret != 0) {
        LOG_ERROR(Lib_Fios2, "ret: {}, len: {}", ret, length);
    }
    LOG_DEBUG(Lib_Fios2, "ret: {}, op: {}", ret, op);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, static_cast<s32>(ret));
    return op;
}

OrbisFiosSize PS4_SYSV_ABI sceFiosFileReadSync(const OrbisFiosOpAttr* pAttr, const char* pPath,
                                               void* pBuf, OrbisFiosSize length,
                                               OrbisFiosOffset offset) {
    LOG_WARNING(Lib_Fios2, "(DUMMY) called, path: {}, length: {}, offset: {}", pPath, length,
                offset);
    std::scoped_lock l{m};
    s64 ret = -1;

    s32 fd = sceKernelOpen(ToApp0(pPath), O_RDONLY, 0);

    if (fd >= 0) {
        ret = sceKernelPread(fd, pBuf, length, offset);
        // ret = std::min(ret, (s64)0);
        sceKernelClose(fd);
    }

    if (ret != length) {
        LOG_ERROR(Lib_Fios2, "ret: {}, len: {}", ret, length);
    }
    LOG_DEBUG(Lib_Fios2, "ret: {}", ret);
    return ret;
}

s32 PS4_SYSV_ABI sceFiosFileTruncate() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosFileTruncateSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosFileWrite() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosFileWriteSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosGetAllDHs() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosGetAllFHs() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosGetAllOps() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosGetDefaultOpAttr() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosGetGlobalDefaultOpAttr() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosGetSuspendCount() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosGetThreadDefaultOpAttr() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosInitialize() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosIOFilterAdd() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosIOFilterCache() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosIOFilterGetInfo() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosIOFilterPsarcDearchiver() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosIOFilterRemove() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosIsIdle() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosIsInitialized() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosIsSuspended() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

bool PS4_SYSV_ABI sceFiosIsValidHandle(OrbisFiosHandle h) {
    LOG_WARNING(Lib_Fios2, "(DUMMY) called, handle: {}", h);
    return h > 2;
}

s32 PS4_SYSV_ABI sceFiosOpCancel() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosOpDelete(OrbisFiosOp op) {
    std::scoped_lock l{m};
    // LOG_DEBUG(Lib_Fios2, "(DUMMY) called, op: {}", op);
    op_return_codes_map.erase(op);
    op_io_return_codes_map.erase(op);
    return ORBIS_OK;
}

OrbisFiosSize PS4_SYSV_ABI sceFiosOpGetActualCount(OrbisFiosOp op) {
    std::scoped_lock l{m};
    LOG_DEBUG(Lib_Fios2, "(DUMMY) called, op: {}", op);
    if (op_io_return_codes_map.find(op) == op_io_return_codes_map.end()) {
        LOG_WARNING(Lib_Fios2, "Bad op handle: {}", op);
        return ORBIS_FIOS_ERROR_BAD_OP;
    }
    return op_io_return_codes_map.find(op)->second;
}

s32 PS4_SYSV_ABI sceFiosOpGetAttr() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosOpGetBuffer() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosOpGetError(OrbisFiosOp op) {
    LOG_DEBUG(Lib_Fios2, "(DUMMY) called, op: {}", op);
    if (op_return_codes_map.find(op) == op_return_codes_map.end()) {
        LOG_DEBUG(Lib_Fios2, "Bad or old op handle: {}", op);
        return ORBIS_FIOS_ERROR_BAD_OP;
    }
    return op_return_codes_map.find(op)->second;
}

s32 PS4_SYSV_ABI sceFiosOpGetOffset() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosOpGetPath() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

OrbisFiosSize PS4_SYSV_ABI sceFiosOpGetRequestCount(OrbisFiosOp op) {
    LOG_WARNING(Lib_Fios2, "(DUMMY) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosOpIsCancelled() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

bool PS4_SYSV_ABI sceFiosOpIsDone(OrbisFiosOp op) {
    LOG_DEBUG(Lib_Fios2, "(DUMMY) called, op: {}", op);
    if (op_return_codes_map.find(op) == op_return_codes_map.end()) {
        if (op_io_return_codes_map.find(op) == op_io_return_codes_map.end()) {
            LOG_ERROR(Lib_Fios2, "Bad op handle: {}", op);
            return false;
        }
    }
    return true;
}

s32 PS4_SYSV_ABI sceFiosOpReschedule() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosOpRescheduleWithPriority() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosOpSetBuffer() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosOpSyncWait(OrbisFiosOp op) {
    std::scoped_lock l{m};
    // LOG_DEBUG(Lib_Fios2, "called, op: {}", op);
    auto it = op_return_codes_map.find(op);
    if (it == op_return_codes_map.end()) {
        auto it1 = op_io_return_codes_map.find(op);
        if (it1 == op_io_return_codes_map.end()) {
            LOG_ERROR(Lib_Fios2, "Bad op handle: {}", op);
            return ORBIS_FIOS_ERROR_BAD_OP;
        }
        OrbisFiosSize ret = it1->second;
        op_io_return_codes_map.erase(it1);
        return ret;
    }
    s32 ret = it->second;
    op_return_codes_map.erase(it);
    return ret;
}

OrbisFiosSize PS4_SYSV_ABI sceFiosOpSyncWaitForIO(OrbisFiosOp op) {
    std::scoped_lock l{m};
    // LOG_DEBUG(Lib_Fios2, "called, op: {}", op);
    auto it = op_io_return_codes_map.find(op);
    if (it == op_io_return_codes_map.end()) {
        auto it1 = op_return_codes_map.find(op);
        if (it1 == op_return_codes_map.end()) {
            LOG_ERROR(Lib_Fios2, "Bad op handle: {}", op);
            return ORBIS_FIOS_ERROR_BAD_OP;
        }
        OrbisFiosSize ret = it1->second;
        op_return_codes_map.erase(it1);
        return ret;
    }
    OrbisFiosSize ret = it->second;
    op_io_return_codes_map.erase(it);
    return ret;
}

s32 PS4_SYSV_ABI sceFiosOpWait(OrbisFiosOp op) {
    std::scoped_lock l{m};
    LOG_DEBUG(Lib_Fios2, "called, op: {}", op);
    auto it = op_return_codes_map.find(op);
    if (it == op_return_codes_map.end()) {
        auto it1 = op_io_return_codes_map.find(op);
        if (it1 == op_io_return_codes_map.end()) {
            LOG_ERROR(Lib_Fios2, "Bad op handle: {}", op);
            return ORBIS_FIOS_ERROR_BAD_OP;
        }
        OrbisFiosSize ret = it1->second;
        op_io_return_codes_map.erase(it1);
        return ret;
    }
    s32 ret = it->second;
    op_return_codes_map.erase(it);
    return ret;
}

s32 PS4_SYSV_ABI sceFiosOpWaitUntil() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosOverlayAdd() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosOverlayGetInfo() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosOverlayGetList() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosOverlayModify() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosOverlayRemove() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosOverlayResolveSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosPathcmp() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosPathncmp() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosPathNormalize() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosPrintf() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosPrintTimeStamps() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosRename() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosRenameSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosResolve() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosResolveSync() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosResume() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosSaveTimeStamp() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosSetGlobalDefaultOpAttr() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosSetThreadDefaultOpAttr() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosShutdownAndCancelOps() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

OrbisFiosOp PS4_SYSV_ABI sceFiosStat(const OrbisFiosOpAttr* pAttr, const char* pPath,
                                     OrbisFiosStat* pOutStatus) {
    LOG_WARNING(Lib_Fios2, "(DUMMY) called pAttr: {} path: {}", (void*)pAttr, pPath);

    OrbisFiosOp op = ++op_count;
    OrbisKernelStat kstat{};
    s32 ret = sceKernelStat(ToApp0(pPath), &kstat);
    if (ret < 0) {
        op_return_codes_map.emplace(op, ORBIS_FIOS_ERROR_BAD_PATH);
        CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ORBIS_FIOS_ERROR_BAD_PATH);
        return op;
    }

    pOutStatus->fileSize = kstat.st_size;
    pOutStatus->accessDate = kstat.st_atim.tv_sec;
    pOutStatus->modificationDate = kstat.st_mtim.tv_sec;
    pOutStatus->creationDate = kstat.st_birthtim.tv_sec;
    pOutStatus->statFlags = 0;
    pOutStatus->reserved = 0;
    pOutStatus->uid = kstat.st_uid;
    pOutStatus->gid = kstat.st_gid;
    pOutStatus->dev = kstat.st_dev;
    pOutStatus->ino = kstat.st_ino;
    pOutStatus->mode = kstat.st_mode;

    op_return_codes_map.emplace(op, ORBIS_OK);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ret);
    return op;
}

s32 PS4_SYSV_ABI sceFiosStatSync(const OrbisFiosOpAttr* pAttr, const char* pPath,
                                 OrbisFiosStat* pOutStatus) {
    LOG_DEBUG(Lib_Fios2, "(DUMMY) called");
    OrbisFiosOp op = sceFiosStat(pAttr, pPath, pOutStatus);
    return sceFiosOpSyncWait(op);
}

s32 PS4_SYSV_ABI sceFiosSuspend() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosTerminate() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosTimeGetCurrent() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

OrbisFiosTimeInterval PS4_SYSV_ABI sceFiosTimeIntervalFromNanoseconds(s64 ns) {
    LOG_INFO(Lib_Fios2, "called");
    return ns;
}

s32 PS4_SYSV_ABI sceFiosTimeIntervalToNanoseconds(OrbisFiosTime interval) {
    LOG_INFO(Lib_Fios2, "called");
    return interval;
}

s32 PS4_SYSV_ABI sceFiosTraceTimestamp() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosUpdateParameters() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceFiosVprintf() {
    LOG_ERROR(Lib_Fios2, "(STUBBED) called");
    return ORBIS_OK;
}

} // namespace Libraries::Fios2