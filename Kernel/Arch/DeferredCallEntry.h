/*
 * Copyright (c) 2020, Tom <tomut@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/AlignedObjectBuffer.h>
#include <AK/BitCast.h>
#include <AK/Function.h>

namespace Kernel {

struct DeferredCallEntry {
    using HandlerFunction = Function<void()>;

    DeferredCallEntry* next;
    AlignedObjectBuffer<HandlerFunction> handler_storage;
    bool was_allocated;

    HandlerFunction& handler_value()
    {
        return handler_storage.object();
    }

    void invoke_handler()
    {
        handler_value()();
    }
};

}
