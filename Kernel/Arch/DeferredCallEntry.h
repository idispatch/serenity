/*
 * Copyright (c) 2020, Tom <tomut@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/BitCast.h>
#include <AK/Function.h>
#include <AK/ObjectBuffer.h>

namespace Kernel {

struct DeferredCallEntry {
    using HandlerFunction = Function<void()>;

    DeferredCallEntry* next;
    ObjectBuffer<HandlerFunction> handler_storage;
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
