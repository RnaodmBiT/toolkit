#pragma once

namespace Cursor {
    enum Type {
        Arrow,
        IBeam,
        Crosshair,
    };

    void initialize();
    void set(Type cursor);
}
