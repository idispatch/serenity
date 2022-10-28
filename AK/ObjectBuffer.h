/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Types.h>

namespace AK {

template<class T>
class ObjectBuffer {
    alignas(T) u8 m_storage[sizeof(T)];

public:
    T* address()
    {
        return reinterpret_cast<T*>(static_cast<void*>(m_storage));
    }

    u8* buffer()
    {
        return m_storage;
    }

    T& object()
    {
        return *reinterpret_cast<T*>(this);
    }

    T const* address() const
    {
        return reinterpret_cast<T const*>(static_cast<void const*>(m_storage));
    }

    u8 const* buffer() const
    {
        return m_storage;
    }

    T const& object() const
    {
        return *reinterpret_cast<T const*>(this);
    }
};

template<class T, size_t Capacity>
class ObjectArrayBuffer {
    static constexpr size_t storage_size()
    {
        if constexpr (Capacity == 0)
            return 0;
        else
            return sizeof(T) * Capacity;
    }

    static constexpr size_t storage_alignment()
    {
        if constexpr (Capacity == 0)
            return 1;
        else
            return alignof(T);
    }

    alignas(storage_alignment()) u8 m_storage[storage_size()];

public:
    T* address(size_t index)
    {
        static_assert(Capacity > 0, "Invalid capacity");
        return reinterpret_cast<T*>(static_cast<void*>(m_storage)) + index;
    }

    u8* buffer()
    {
        static_assert(Capacity > 0, "Invalid capacity");
        return m_storage;
    }

    T& object(size_t index)
    {
        return *address(index);
    }

    T const* address(size_t index) const
    {
        static_assert(Capacity > 0, "Invalid capacity");
        return reinterpret_cast<T const*>(static_cast<void const*>(m_storage)) + index;
    }

    u8 const* buffer() const
    {
        static_assert(Capacity > 0, "Invalid capacity");
        return m_storage;
    }

    T const& object(size_t index) const
    {
        return *address(index);
    }
};

}

using AK::ObjectArrayBuffer;
using AK::ObjectBuffer;
