#include <util/bytes.h>
#include "InMemoryStateBackend.h"

#define MASTER_KEY_PREFIX "master_"

namespace state {
    InMemoryStateBackend::InMemoryStateBackend() : redis(redis::Redis::getState()),
                                                   thisIP(util::getSystemConfig().endpointHost) {

    }

    std::string getKeyForMasterLookup(const std::string &key) {
        return MASTER_KEY_PREFIX + key;
    }

    std::string InMemoryStateBackend::getMasterIP(const std::string &key) {
        const std::string masterKey = getKeyForMasterLookup(key);
        const std::vector<uint8_t> masterIPBytes = redis.get(masterKey);
        const std::string masterIP = util::bytesToString(masterIPBytes);
    }

    std::string InMemoryStateBackend::getMasterForGet(const std::string &key) {
        const std::string ip = getMasterIP(key);
        if (ip.empty()) {
            throw std::runtime_error("No master set for " + key);
        }

        if (ip == thisIP) {
            throw std::runtime_error("This host is master for " + key);
        }

        return ip;
    }

    size_t InMemoryStateBackend::getSize(const std::string &key) {
        // TODO - implement
        return 0;
    }

    void InMemoryStateBackend::get(const std::string &key, uint8_t *buffer, size_t bufferLen) {
        const std::string keyMaster = getMasterForGet(key);

        // TODO - pull value from master
    }

    std::vector<uint8_t> InMemoryStateBackend::get(const std::string &key) {
        const std::string keyMaster = getMasterForGet(key);

        // TODO - pull value from master
        std::vector<uint8_t> empty;
        return empty;
    }

    void InMemoryStateBackend::getRange(const std::string &key, uint8_t *buffer, size_t bufferLen,
                                        long start, long end) {
        const std::string keyMaster = getMasterForGet(key);

        // TODO - pull value from master
    }

    void InMemoryStateBackend::set(const std::string &key, const uint8_t *value, size_t size) {
        const std::string keyMaster = getMasterIP(key);

        // TODO - implement
    }

    void InMemoryStateBackend::set(const std::string &key, const std::vector<uint8_t> &value) {
        // TODO - implement
    }

    long InMemoryStateBackend::acquireLock(const std::string &key, int expirySeconds) {
        // TODO - implement
        return 0;
    }

    void InMemoryStateBackend::releaseLock(const std::string &key, long lockId) {
        // TODO - implement
    }

    void InMemoryStateBackend::del(const std::string &key) {
        // TODO - implement
    }

    void
    InMemoryStateBackend::setRangePipeline(const std::string &key, long offset, const uint8_t *value, size_t size) {
        // TODO - implement
    }

    void InMemoryStateBackend::flushPipeline(long pipelineLength) {
        // TODO - implement
    }

    void InMemoryStateBackend::enqueueBytes(const std::string &queueName, const std::vector<uint8_t> &value) {
        // TODO - implement
    }

    void InMemoryStateBackend::dequeueMultiple(const std::string &queueName, uint8_t *buff, long buffLen, long nElems) {
        // TODO - implement
    }

    long InMemoryStateBackend::incrByLong(const std::string &key, long value) {
        // TODO - implement
        return 0;
    }

    void InMemoryStateBackend::setLong(const std::string &key, long value) {
        // TODO - implement
    }

    long InMemoryStateBackend::getLong(const std::string &key) {
        const std::string keyMaster = getMasterForGet(key);

        // TODO - implement
        return 0;
    }
}