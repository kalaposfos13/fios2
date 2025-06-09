// SPDX-FileCopyrightText: Copyright 2025 shadPS4 Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "assert.h"
#include "fios2.h"
#include "fios2_error.h"
#include "logging.h"
#include "types.h"

#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include <orbis/libkernel.h>
// #include "orbis/_types/kernel.h"

extern "C" void _start() {
    return; // shut up compiler
}

namespace Fios2 {

std::mutex m;

OrbisFiosOp op_count = 0;

std::unordered_map<OrbisFiosOp, s32>* op_return_codes_map = nullptr;
std::unordered_map<OrbisFiosOp, OrbisFiosSize>* op_io_return_codes_map = nullptr;

std::unordered_map<OrbisFiosFH, std::string>* fh_path_map = nullptr;
std::unordered_map<OrbisFiosDH, std::string>* dh_path_map = nullptr;

std::unordered_map<std::string, _OrbisKernelStat>* file_stat_map = nullptr;

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

void EnsureMapsInitialized() {
    if (op_return_codes_map == nullptr) [[unlikely]] {
        LOG_INFO("Initializing maps");
        op_return_codes_map = new std::unordered_map<OrbisFiosOp, s32>();
        op_io_return_codes_map = new std::unordered_map<OrbisFiosOp, OrbisFiosSize>();
        fh_path_map = new std::unordered_map<OrbisFiosFH, std::string>();
        dh_path_map = new std::unordered_map<OrbisFiosDH, std::string>();
        file_stat_map = new std::unordered_map<std::string, _OrbisKernelStat>();
    }
}

void CallFiosCallback(const OrbisFiosOpAttr* pAttr, OrbisFiosOp op, OrbisFiosOpEvent event,
                      s32 err) {
    if (pAttr && pAttr->pCallback) {
        // LOG_INFO("Calling callback at {}, for op: {}", (void*)pAttr->pCallback, op);
        int ret = pAttr->pCallback(pAttr->pCallbackContext, op, event, err);
        if (ret != 0) {
            LOG_WARNING("Callback returned {}", ret);
        }
        // LOG_DEBUG("Callback returned");
        // std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

u8 sceFiosArchiveGetDecompressorThreadCount() {
    LOG_ERROR("(STUBBED) called");
    return 1;
}

OrbisFiosOp sceFiosArchiveGetMountBufferSize(const OrbisFiosOpAttr* pAttr, const char* pArchivePath,
                                             const OrbisFiosOpenParams* pOpenParams) {
    LOG_ERROR("(STUBBED) called");
    // code
    OrbisFiosOp op = ++op_count;
    op_return_codes_map->emplace(op, ORBIS_OK);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ORBIS_OK);
    return op;
}

s32 sceFiosArchiveGetMountBufferSizeSync(const OrbisFiosOpAttr* pAttr, const char* pArchivePath,
                                         const OrbisFiosOpenParams* pOpenParams) {
    LOG_ERROR("(STUBBED) called");
    OrbisFiosOp op = sceFiosArchiveGetMountBufferSize(pAttr, pArchivePath, pOpenParams);
    return sceFiosOpSyncWait(op);
}

OrbisFiosOp sceFiosArchiveMount(const OrbisFiosOpAttr* pAttr, OrbisFiosFH* pOutFH,
                                const char* pArchivePath, const char* pMountPoint,
                                OrbisFiosBuffer mountBuffer,
                                const OrbisFiosOpenParams* pOpenParams) {
    LOG_ERROR("(STUBBED) called");
    OrbisFiosOp op = ++op_count;
    op_return_codes_map->emplace(op, ORBIS_OK);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ORBIS_OK);
    return op;
}

s32 sceFiosArchiveMountSync(const OrbisFiosOpAttr* pAttr, OrbisFiosFH* pOutFH,
                            const char* pArchivePath, const char* pMountPoint,
                            OrbisFiosBuffer mountBuffer, const OrbisFiosOpenParams* pOpenParams) {
    LOG_ERROR("(STUBBED) called");
    OrbisFiosOp op =
        sceFiosArchiveMount(pAttr, pOutFH, pArchivePath, pMountPoint, mountBuffer, pOpenParams);
    return sceFiosOpSyncWait(op);
}

OrbisFiosOp sceFiosArchiveMountWithOrder() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosArchiveMountWithOrderSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosArchiveSetDecompressorThreadCount() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosArchiveUnmount() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosArchiveUnmountSync() {
    LOG_ERROR("(STUBBED) called");

    return ORBIS_OK;
}

s32 sceFiosCacheContainsFileRangeSync() {
    LOG_ERROR("(STUBBED) called");

    return ORBIS_OK;
}

s32 sceFiosCacheContainsFileSync() {
    LOG_ERROR("(STUBBED) called");

    return ORBIS_OK;
}

s32 sceFiosCacheFlushFileRangeSync() {
    LOG_ERROR("(STUBBED) called");

    return ORBIS_OK;
}

s32 sceFiosCacheFlushFileSync() {
    LOG_ERROR("(STUBBED) called");

    return ORBIS_OK;
}

s32 sceFiosCacheFlushSync() {
    LOG_ERROR("(STUBBED) called");

    return ORBIS_OK;
}

s32 sceFiosCachePrefetchFH() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosCachePrefetchFHRange() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosCachePrefetchFHRangeSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosCachePrefetchFHSync() {
    LOG_ERROR("(STUBBED) called");

    return ORBIS_OK;
}

s32 sceFiosCachePrefetchFile() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosCachePrefetchFileRange() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosCachePrefetchFileRangeSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosCachePrefetchFileSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosCancelAllOps() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosClearTimeStamps() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosCloseAllFiles() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

OrbisFiosDate sceFiosDateFromComponents(tm* pComponents) {
    LOG_INFO("called");
    return mktime(pComponents) * 1000000000;
}

OrbisFiosDate sceFiosDateGetCurrent() {
    LOG_INFO("called");
    return time(nullptr) * 1000000000;
}

tm* sceFiosDateToComponents(OrbisFiosDate date, tm* pOutComponents) {
    LOG_INFO("called");
    time_t t = date / 1000000000;
    pOutComponents = gmtime(&t);
    return pOutComponents;
}

s32 sceFiosDeallocatePassthruFH() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosDebugDumpDate() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosDebugDumpDH() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosDebugDumpError() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosDebugDumpFH() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosDebugDumpOp() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosDelete() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosDeleteSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosDHClose(const OrbisFiosOpAttr* pAttr, OrbisFiosDH dh) {
    EnsureMapsInitialized();
    std::scoped_lock l{m};
    LOG_WARNING("(STUBBED) called, dh: {}", dh);
    s32 ret = sceKernelClose(dh);
    dh_path_map->erase(dh);
    OrbisFiosOp op = ++op_count;
    op_return_codes_map->emplace(op, dh);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ret);
    return op;
}

s32 sceFiosDHCloseSync(const OrbisFiosOpAttr* pAttr, OrbisFiosDH dh) {
    LOG_DEBUG("(DUMMY) called");
    OrbisFiosOp op = sceFiosDHClose(pAttr, dh);
    return sceFiosOpSyncWait(op);
}

s32 sceFiosDHGetPath() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

OrbisFiosOp sceFiosDHOpen(const OrbisFiosOpAttr* pAttr, OrbisFiosDH* pOutDH, const char* pPath,
                          OrbisFiosBuffer buf) {
    EnsureMapsInitialized();
    std::scoped_lock l{m};
    LOG_WARNING("(DUMMY) called, path: {}", pPath);

    s32 dh = sceKernelOpen(ToApp0(pPath), O_DIRECTORY, 0);
    dh_path_map->emplace(dh, pPath);

    if (pOutDH) {
        *pOutDH = dh;
    }

    OrbisFiosOp op = ++op_count;
    op_return_codes_map->emplace(op, dh);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, dh);
    return op;
}

s32 sceFiosDHOpenSync(const OrbisFiosOpAttr* pAttr, OrbisFiosDH* pOutDH, const char* pPath,
                      OrbisFiosBuffer buf) {
    LOG_DEBUG("(DUMMY) called");
    OrbisFiosOp op = sceFiosDHOpen(pAttr, pOutDH, pPath, buf);
    return sceFiosOpSyncWait(op);
}

OrbisFiosOp sceFiosDHRead(const OrbisFiosOpAttr* pAttr, OrbisFiosDH dh,
                          OrbisFiosDirEntry* pOutEntry) {
    LOG_WARNING("(DUMMY) called");

    UNREACHABLE_MSG("todo");

    OrbisFiosOp op = ++op_count;
    op_return_codes_map->emplace(op, ORBIS_OK);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ORBIS_OK);
    return op;
}

s32 sceFiosDHReadSync(const OrbisFiosOpAttr* pAttr, OrbisFiosDH dh, OrbisFiosDirEntry* pOutEntry) {
    LOG_DEBUG("(DUMMY) called");
    OrbisFiosOp op = sceFiosDHRead(pAttr, dh, pOutEntry);
    return sceFiosOpSyncWait(op);
}

s32 sceFiosDirectoryCreate() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosDirectoryCreateSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosDirectoryCreateWithMode() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosDirectoryCreateWithModeSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosDirectoryDelete() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosDirectoryDeleteSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

bool sceFiosDirectoryExists() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

bool sceFiosDirectoryExistsSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosDLLInitialize() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosDLLTerminate() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

OrbisFiosOp sceFiosExists(const OrbisFiosOpAttr* pAttr, const char* pPath, bool* pOutExists) {
    OrbisFiosOp op = ++op_count;
    s32 ret;
    {
        EnsureMapsInitialized();
        std::scoped_lock l{m};
        std::string path_str = std::string(ToApp0(pPath));
        auto cache_it = file_stat_map->find(path_str);
        if (cache_it == file_stat_map->end()) /* no cache hit */ {
            LOG_INFO("(DUMMY) called pAttr: {} path: {}", (void*)pAttr, pPath);
            _OrbisKernelStat stat{};
            bool exists = (sceKernelStat(ToApp0(pPath), (OrbisKernelStat*)&stat) == ORBIS_OK);
            if (pOutExists) {
                *pOutExists = exists;
            }
            ret = exists ? 1 : 0;
            op_return_codes_map->emplace(op, ret);
            file_stat_map->emplace(path_str, stat); // add to cache
        } else /* cache hit */ {
            bool exists = cache_it->second.st_mode != 0;
            if (pOutExists) {
                *pOutExists = exists;
            }
            ret = exists ? 1 : 0;
            op_return_codes_map->emplace(op, ret);
        }
    }
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ret);
    // LOG_DEBUG("ret: {}, op: {}", ret, op);
    return op;
}

bool sceFiosExistsSync(const OrbisFiosOpAttr* pAttr, const char* pPath) {
    // LOG_DEBUG("(DUMMY) called");
    if (pAttr && pAttr->pCallback) {
        LOG_WARNING("There is a callback to a sync function!");
    }
    OrbisFiosOp op = sceFiosExists(pAttr, pPath, nullptr);
    return static_cast<bool>(sceFiosOpSyncWait(op));
}

s32 sceFiosFHClose(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh) {
    EnsureMapsInitialized();
    std::scoped_lock l{m};
    LOG_WARNING("(DUMMY) called pAttr: {} fh: {}", (void*)pAttr, fh);
    OrbisFiosOp op = ++op_count;
    s32 ret = sceKernelClose(fh);
    op_return_codes_map->emplace(op, ret);
    fh_path_map->erase(fh);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ret);
    return op;
}

s32 sceFiosFHCloseSync(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh) {
    LOG_WARNING("(DUMMY) called");
    if (pAttr && pAttr->pCallback) {
        LOG_WARNING("There is a callback to a sync function!");
    }
    OrbisFiosOp op = sceFiosFHClose(pAttr, fh);
    return sceFiosOpSyncWait(op);
}

s32 sceFiosFHGetOpenParams() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

const char* sceFiosFHGetPath(OrbisFiosFH fh) {
    EnsureMapsInitialized();
    std::scoped_lock l{m};
    LOG_WARNING("(DUMMY) called");

    auto it = fh_path_map->find(fh);
    if (it != fh_path_map->end()) {
        return it->second.c_str();
    }
    LOG_ERROR("Invalid FH: {}", fh);
    return nullptr;
}

OrbisFiosSize sceFiosFHGetSize(OrbisFiosFH fh) {
    EnsureMapsInitialized();
    std::scoped_lock l{m};
    LOG_WARNING("(DUMMY) called, fh: {}", (u32)fh);
    if (!sceFiosIsValidHandle(fh)) {
        return -1;
    }
    _OrbisKernelStat sb{};
    sceKernelFstat(fh, (OrbisKernelStat*)&sb);
    return sb.st_size;
}

OrbisFiosOp sceFiosFHOpenWithMode(const OrbisFiosOpAttr* pAttr, OrbisFiosFH* pOutFH,
                                  const char* pPath, const OrbisFiosOpenParams* pOpenParams,
                                  s32 nativeMode) {
    EnsureMapsInitialized();
    std::scoped_lock l{m};
    LOG_DEBUG("(DUMMY) called, path: {}", pPath);
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
    s32 fh = sceKernelOpen(ToApp0(pPath),
                           (open_params & 0x1000) << 4 | (open_params << 6) & 0x400 |
                               (open_params << 6) & 0x200 | (open_params << 1) & 8 | open_param,
                           mode);
    fh_path_map->emplace(fh, pPath);
    if (pOutFH) {
        *pOutFH = fh;
    }
    OrbisFiosOp op = ++op_count;
    s32 ret = std::min(fh, ORBIS_OK);

    op_return_codes_map->emplace(op, ret);

    LOG_INFO("ret: {}, op: {}, fh: {}", ret, op, fh);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ret);
    // pros: it fixes a race condition in GRR
    // cons: I don't know why it works
    std::this_thread::sleep_for(std::chrono::nanoseconds(2));
    return op;
}

s32 sceFiosFHOpenWithModeSync(const OrbisFiosOpAttr* pAttr, OrbisFiosFH* pOutFH, const char* pPath,
                              const OrbisFiosOpenParams* pOpenParams, s32 nativeMode) {
    LOG_DEBUG("(DUMMY) called");
    if (pAttr && pAttr->pCallback) {
        LOG_WARNING("There is a callback to a sync function!");
    }
    OrbisFiosOp op = sceFiosFHOpenWithMode(pAttr, pOutFH, pPath, pOpenParams, nativeMode);
    return sceFiosOpSyncWait(op);
}

OrbisFiosOp sceFiosFHOpen(const OrbisFiosOpAttr* pAttr, OrbisFiosFH* pOutFH, const char* pPath,
                          const OrbisFiosOpenParams* pOpenParams) {
    LOG_WARNING("(DUMMY) called");
    return sceFiosFHOpenWithMode(pAttr, pOutFH, pPath, pOpenParams, -1);
}

s32 sceFiosFHOpenSync(const OrbisFiosOpAttr* pAttr, OrbisFiosFH* pOutFH, const char* pPath,
                      const OrbisFiosOpenParams* pOpenParams) {
    LOG_DEBUG("(DUMMY) called");
    if (pAttr && pAttr->pCallback) {
        LOG_WARNING("There is a callback to a sync function!");
    }
    OrbisFiosOp op = sceFiosFHOpen(pAttr, pOutFH, pPath, pOpenParams);
    return sceFiosOpSyncWait(op);
}

OrbisFiosOp sceFiosFHPread(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh, void* pBuf,
                           OrbisFiosSize length, OrbisFiosOffset offset) {
    EnsureMapsInitialized();
    std::scoped_lock l{m};
    // LOG_WARNING("(DUMMY) called, fh: {}, length: {}, offset: {}", fh,
    // length);
    OrbisFiosSize ret = sceKernelPread(fh, pBuf, length, offset);
    OrbisFiosOp op = ++op_count;
    op_io_return_codes_map->emplace(op, ret);
    // LOG_DEBUG("fh: {}, ret: {}, op: {}", fh, ret, op);
    if (ret != length) {
        LOG_ERROR("len: {}, ret: {}", length, ret);
    }
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ret);
    return op;
}

s32 sceFiosFHPreadSync(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh, void* pBuf,
                       OrbisFiosSize length, OrbisFiosOffset offset) {
    // LOG_DEBUG("(DUMMY) called");
    if (pAttr && pAttr->pCallback) {
        LOG_WARNING("There is a callback to a sync function!");
    }
    OrbisFiosOp op = sceFiosFHPread(pAttr, fh, pBuf, length, offset);
    return sceFiosOpSyncWaitForIO(op);
}

s32 sceFiosFHPreadv() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosFHPreadvSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosFHPwrite() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosFHPwriteSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosFHPwritev() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosFHPwritevSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

OrbisFiosOp sceFiosFHRead(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh, void* pBuf,
                          OrbisFiosSize length) {
    EnsureMapsInitialized();
    std::scoped_lock l{m};
    // LOG_WARNING("(DUMMY) called, fh: {}, length: {:#x}", fh, (u64)length);
    OrbisFiosSize ret = sceKernelRead(fh, pBuf, length);
    OrbisFiosOp op = ++op_count;
    if (ret != length) {
        LOG_ERROR("len: {}, ret: {}", length, ret);
    }
    op_io_return_codes_map->emplace(op, ret);
    // LOG_DEBUG("ret: {}, op: {}", ret, op);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ret);
    return op;
}

OrbisFiosSize sceFiosFHReadSync(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh, void* pBuf,
                                OrbisFiosSize length) {
    // LOG_DEBUG("(DUMMY) called");
    if (pAttr && pAttr->pCallback) {
        LOG_WARNING("There is a callback to a sync function!");
    }
    OrbisFiosOp op = sceFiosFHRead(pAttr, fh, pBuf, length);
    return sceFiosOpSyncWaitForIO(op);
}

OrbisFiosOp sceFiosFHReadv(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh,
                           const OrbisFiosBuffer iov[], int iovcnt) {
    EnsureMapsInitialized();
    std::scoped_lock l{m};
    LOG_WARNING("(DUMMY) called");

    std::vector<OrbisKernelIovec> kernel_iov(iovcnt);
    for (int i = 0; i < iovcnt; ++i) {
        kernel_iov[i].base = iov[i].pPtr;
        kernel_iov[i].len = static_cast<std::size_t>(iov[i].length);
    }

    s64 ret = sceKernelPreadv(fh, kernel_iov.data(), iovcnt, 0);

    OrbisFiosOp op = ++op_count;
    op_io_return_codes_map->emplace(op, ret);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ret);
    return op;
}

OrbisFiosSize sceFiosFHReadvSync(const OrbisFiosOpAttr* pAttr, OrbisFiosFH fh,
                                 const OrbisFiosBuffer iov[], int iovcnt) {
    LOG_DEBUG("(DUMMY) called");
    if (pAttr && pAttr->pCallback) {
        LOG_WARNING("There is a callback to a sync function!");
    }
    OrbisFiosOp op = sceFiosFHReadv(pAttr, fh, iov, iovcnt);
    return sceFiosOpSyncWaitForIO(op);
}

s32 sceFiosFHSeek(OrbisFiosFH fh, OrbisFiosOffset offset, OrbisFiosWhence whence) {
    LOG_WARNING("(DUMMY) called");
    return sceKernelLseek(fh, offset, whence);
}

s32 sceFiosFHStat() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosFHStatSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosFHSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosFHSyncSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosFHTell(OrbisFiosFH fh) {
    LOG_WARNING("(DUMMY) called");
    return sceKernelLseek(fh, 0, SceFiosWhence::Current);
}

s32 sceFiosFHToFileno() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosFHTruncate() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosFHTruncateSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosFHWrite() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosFHWriteSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosFHWritev() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosFHWritevSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosFileDelete() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosFileDeleteSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

OrbisFiosOp sceFiosFileExists(const OrbisFiosOpAttr* pAttr, const char* pPath) {
    // LOG_WARNING("(DUMMY) called");
    return sceFiosExists(pAttr, pPath, nullptr);
}

bool sceFiosFileExistsSync(const OrbisFiosOpAttr* pAttr, const char* pPath) {
    // LOG_DEBUG("(DUMMY) called");
    if (pAttr && pAttr->pCallback) {
        LOG_WARNING("There is a callback to a sync function!");
    }
    OrbisFiosOp op = sceFiosFileExists(pAttr, pPath);
    return sceFiosOpSyncWaitForIO(op);
}

OrbisFiosOp sceFiosFileGetSize(const OrbisFiosOpAttr* pAttr, const char* pPath) {
    EnsureMapsInitialized();
    std::scoped_lock l{m};
    OrbisFiosOp op = ++op_count;
    _OrbisKernelStat stat{};
    std::string path_str = std::string(ToApp0(pPath));
    bool exists;
    auto cache_it = file_stat_map->find(path_str);
    if (cache_it == file_stat_map->end()) /* no cache hit */ {
        LOG_DEBUG("No cache hit");
        exists = sceKernelStat(ToApp0(pPath), (OrbisKernelStat*)&stat) == ORBIS_OK;
        file_stat_map->emplace(path_str, stat); // add to cache
    } else {
        LOG_DEBUG("Cache hit");
        exists = cache_it->second.st_mode != 0;
        stat = cache_it->second;
    }
    if (!exists) { // here
        LOG_DEBUG("File {} does not exist", pPath);
        op_io_return_codes_map->emplace(op, ORBIS_FIOS_ERROR_BAD_PATH);
        return op;
    }
    LOG_WARNING("(DUMMY) called pAttr: {} path: {} size: {}, op: {}", (void*)pAttr, pPath,
                stat.st_size, op);
    op_io_return_codes_map->emplace(op, stat.st_size);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, static_cast<s32>(stat.st_size));
    return op;
}

OrbisFiosSize sceFiosFileGetSizeSync(const OrbisFiosOpAttr* pAttr, const char* pPath) {
    LOG_DEBUG("(DUMMY) called");
    OrbisFiosOp op = sceFiosFileGetSize(pAttr, pPath);
    return sceFiosOpSyncWaitForIO(op);
}

s32 sceFiosFilenoToFH() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

OrbisFiosOp sceFiosFileRead(const OrbisFiosOpAttr* pAttr, const char* pPath, void* pBuf,
                            OrbisFiosSize length, OrbisFiosOffset offset) {
    EnsureMapsInitialized();
    std::scoped_lock l{m};
    LOG_WARNING("(DUMMY) called, path: {}, length: {}, offset: {}", pPath, length, offset);
    OrbisFiosOp op = ++op_count;
    s64 ret = -1;

    s32 fd = sceKernelOpen(ToApp0(pPath), O_RDONLY, 0);

    if (fd >= 0) {
        ret = sceKernelPread(fd, pBuf, length, offset);
        ret = std::min(ret, (s64)0);
        sceKernelClose(fd);
    }

    op_io_return_codes_map->emplace(op, ret >= 0 ? ret : ORBIS_FIOS_ERROR_BAD_PATH);
    if (ret != 0) {
        LOG_ERROR("ret: {}, len: {}", ret, length);
    }
    LOG_DEBUG("ret: {}, op: {}", ret, op);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, static_cast<s32>(ret));
    return op;
}

OrbisFiosSize sceFiosFileReadSync(const OrbisFiosOpAttr* pAttr, const char* pPath, void* pBuf,
                                  OrbisFiosSize length, OrbisFiosOffset offset) {
    EnsureMapsInitialized();
    std::scoped_lock l{m};
    LOG_WARNING("(DUMMY) called, path: {}, length: {}, offset: {}", pPath, length, offset);
    s64 ret = -1;

    s32 fd = sceKernelOpen(ToApp0(pPath), O_RDONLY, 0);

    if (fd >= 0) {
        ret = sceKernelPread(fd, pBuf, length, offset);
        // ret = std::min(ret, (s64)0);
        sceKernelClose(fd);
    }

    if (ret != length) {
        LOG_ERROR("ret: {}, len: {}", ret, length);
    }
    LOG_DEBUG("ret: {}", ret);
    return ret;
}

s32 sceFiosFileTruncate() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosFileTruncateSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosFileWrite() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosFileWriteSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosGetAllDHs() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosGetAllFHs() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosGetAllOps() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosGetDefaultOpAttr() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosGetGlobalDefaultOpAttr() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosGetSuspendCount() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosGetThreadDefaultOpAttr() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosInitialize() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosIOFilterAdd() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosIOFilterCache() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosIOFilterGetInfo() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosIOFilterPsarcDearchiver() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosIOFilterRemove() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosIsIdle() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosIsInitialized() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosIsSuspended() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

bool sceFiosIsValidHandle(OrbisFiosHandle h) {
    LOG_DEBUG("(DUMMY) called, handle: {}", h);
    bool ret = h > 2;
    if (!ret) {
        LOG_ERROR("Invalid handle: {}", h);
    }
    return ret;
}

s32 sceFiosOpCancel() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosOpDelete(OrbisFiosOp op) {
    EnsureMapsInitialized();
    std::scoped_lock l{m};
    // LOG_DEBUG("(DUMMY) called, op: {}", op);
    op_return_codes_map->erase(op);
    op_io_return_codes_map->erase(op);
    return ORBIS_OK;
}

OrbisFiosSize sceFiosOpGetActualCount(OrbisFiosOp op) {
    EnsureMapsInitialized();
    std::scoped_lock l{m};
    LOG_DEBUG("(DUMMY) called, op: {}", op);
    if (op_io_return_codes_map->find(op) == op_io_return_codes_map->end()) {
        LOG_WARNING("Bad op handle: {}", op);
        return ORBIS_FIOS_ERROR_BAD_OP;
    }
    return op_io_return_codes_map->find(op)->second;
}

s32 sceFiosOpGetAttr() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosOpGetBuffer() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosOpGetError(OrbisFiosOp op) {
    LOG_DEBUG("(DUMMY) called, op: {}", op);
    if (op_return_codes_map->find(op) == op_return_codes_map->end()) {
        LOG_DEBUG("Bad or old op handle: {}", op);
        return ORBIS_FIOS_ERROR_BAD_OP;
    }
    return op_return_codes_map->find(op)->second;
}

s32 sceFiosOpGetOffset() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosOpGetPath() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

OrbisFiosSize sceFiosOpGetRequestCount(OrbisFiosOp op) {
    LOG_WARNING("(DUMMY) called");
    return ORBIS_OK;
}

s32 sceFiosOpIsCancelled() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

bool sceFiosOpIsDone(OrbisFiosOp op) {
    LOG_DEBUG("(DUMMY) called, op: {}", op);
    if (op_return_codes_map->find(op) == op_return_codes_map->end()) {
        if (op_io_return_codes_map->find(op) == op_io_return_codes_map->end()) {
            LOG_ERROR("Bad op handle: {}", op);
            return false;
        }
    }
    return true;
}

s32 sceFiosOpReschedule() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosOpRescheduleWithPriority() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosOpSetBuffer() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosOpSyncWait(OrbisFiosOp op) {
    EnsureMapsInitialized();
    std::scoped_lock l{m};
    // LOG_DEBUG("called, op: {}", op);
    auto it = op_return_codes_map->find(op);
    if (it == op_return_codes_map->end()) {
        auto it1 = op_io_return_codes_map->find(op);
        if (it1 == op_io_return_codes_map->end()) {
            LOG_ERROR("Bad op handle: {}", op);
            return ORBIS_FIOS_ERROR_BAD_OP;
        }
        OrbisFiosSize ret = it1->second;
        op_io_return_codes_map->erase(it1);
        return ret;
    }
    s32 ret = it->second;
    op_return_codes_map->erase(it);
    return ret;
}

OrbisFiosSize sceFiosOpSyncWaitForIO(OrbisFiosOp op) {
    EnsureMapsInitialized();
    std::scoped_lock l{m};
    // LOG_DEBUG("called, op: {}", op);
    auto it = op_io_return_codes_map->find(op);
    if (it == op_io_return_codes_map->end()) {
        auto it1 = op_return_codes_map->find(op);
        if (it1 == op_return_codes_map->end()) {
            LOG_ERROR("Bad op handle: {}", op);
            return ORBIS_FIOS_ERROR_BAD_OP;
        }
        OrbisFiosSize ret = it1->second;
        op_return_codes_map->erase(it1);
        return ret;
    }
    OrbisFiosSize ret = it->second;
    op_io_return_codes_map->erase(it);
    return ret;
}

s32 sceFiosOpWait(OrbisFiosOp op) {
    EnsureMapsInitialized();
    std::scoped_lock l{m};
    LOG_DEBUG("called, op: {}", op);
    auto it = op_return_codes_map->find(op);
    if (it == op_return_codes_map->end()) {
        auto it1 = op_io_return_codes_map->find(op);
        if (it1 == op_io_return_codes_map->end()) {
            LOG_ERROR("Bad op handle: {}", op);
            return ORBIS_FIOS_ERROR_BAD_OP;
        }
        OrbisFiosSize ret = it1->second;
        op_io_return_codes_map->erase(it1);
        return ret;
    }
    s32 ret = it->second;
    op_return_codes_map->erase(it);
    return ret;
}

s32 sceFiosOpWaitUntil() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosOverlayAdd() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosOverlayGetInfo() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosOverlayGetList() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosOverlayModify() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosOverlayRemove() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosOverlayResolveSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosPathcmp() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosPathncmp() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosPathNormalize() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosPrintf() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosPrintTimeStamps() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosRename() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosRenameSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosResolve() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosResolveSync() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosResume() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosSaveTimeStamp() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosSetGlobalDefaultOpAttr() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosSetThreadDefaultOpAttr() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosShutdownAndCancelOps() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

OrbisFiosOp sceFiosStat(const OrbisFiosOpAttr* pAttr, const char* pPath,
                        OrbisFiosStat* pOutStatus) {
    LOG_WARNING("(DUMMY) called pAttr: {} path: {}", (void*)pAttr, pPath);

    OrbisFiosOp op = ++op_count;
    _OrbisKernelStat stat{};
    s32 ret = sceKernelStat(ToApp0(pPath), (OrbisKernelStat*)&stat);
    if (ret < 0) {
        op_return_codes_map->emplace(op, ORBIS_FIOS_ERROR_BAD_PATH);
        CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ORBIS_FIOS_ERROR_BAD_PATH);
        return op;
    }

    pOutStatus->fileSize = stat.st_size;
    pOutStatus->accessDate = stat.st_atim.tv_sec;
    pOutStatus->modificationDate = stat.st_mtim.tv_sec;
    pOutStatus->creationDate = stat.st_birthtim.tv_sec;
    pOutStatus->statFlags = 0;
    pOutStatus->reserved = 0;
    pOutStatus->uid = stat.st_uid;
    pOutStatus->gid = stat.st_gid;
    pOutStatus->dev = stat.st_dev;
    pOutStatus->ino = stat.st_ino;
    pOutStatus->mode = stat.st_mode;

    op_return_codes_map->emplace(op, ORBIS_OK);
    CallFiosCallback(pAttr, op, OrbisFiosOpEvents::Complete, ret);
    return op;
}

s32 sceFiosStatSync(const OrbisFiosOpAttr* pAttr, const char* pPath, OrbisFiosStat* pOutStatus) {
    LOG_DEBUG("(DUMMY) called");
    OrbisFiosOp op = sceFiosStat(pAttr, pPath, pOutStatus);
    return sceFiosOpSyncWait(op);
}

s32 sceFiosSuspend() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosTerminate() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosTimeGetCurrent() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

OrbisFiosTimeInterval sceFiosTimeIntervalFromNanoseconds(s64 ns) {
    LOG_INFO("called");
    return ns;
}

s32 sceFiosTimeIntervalToNanoseconds(OrbisFiosTime interval) {
    LOG_INFO("called");
    return interval;
}

s32 sceFiosTraceTimestamp() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosUpdateParameters() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

s32 sceFiosVprintf() {
    LOG_ERROR("(STUBBED) called");
    return ORBIS_OK;
}

} // namespace Fios2
