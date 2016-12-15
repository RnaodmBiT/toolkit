#pragma once
#include <core.hpp>
using namespace tk::core;

template <class T, class ...Args>
class Factory {
public:
    typedef std::function<T(Args&..., Blob::const_iterator&)> Builder;

private:
    std::map<std::string, Builder> types;

public:
    T buildFromData(const std::string& type, Args&... args, Blob::const_iterator& blob) {
        tk_assert(types.count(type), format("Type %% not found in factory", type));
        tk_info(format("Building object %%", type));
        return types[type](args..., blob);
    }

    template <class ...Values>
    T build(const std::string& type, Args&... args, const Values&... values) {
        Blob blob;
        serialize(blob, values...);
        Blob::const_iterator it = blob.begin();
        return buildFromData(type, args..., it);
    }

    void addType(const std::string& type, Builder func) {
        types[type] = func;
    }
};
