#pragma once

#include <map>

enum RenderingLayer {
    USER_INTERFACE
};


namespace Constants {
    inline std::map<RenderingLayer, float> LAYER_INDEXES = {
        {RenderingLayer::USER_INTERFACE, -0.9f}
    };
}
