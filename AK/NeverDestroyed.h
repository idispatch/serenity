/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/AlignedObjectBuffer.h>
#include <AK/Noncopyable.h>
#include <AK/Types.h>

namespace AK {

template<typename T>
class NeverDestroyed {
    AK_MAKE_NONCOPYABLE(NeverDestroyed);
    AK_MAKE_NONMOVABLE(NeverDestroyed);

public:
    template<typename... Args>
    NeverDestroyed(Args&&... args)
    {
        new (storage.buffer()) T(forward<Args>(args)...);
    }

    ~NeverDestroyed() = default;

    T* operator->() { return &get(); }
    T const* operator->() const { return &get(); }

    T& operator*() { return get(); }
    T const& operator*() const { return get(); }

    T& get() { return storage.object(); }
    T const& get() const { return storage.object(); }

private:
    AlignedObjectBuffer<T> storage;
};

}

using AK::NeverDestroyed;
