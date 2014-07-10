/*
 * DISTRHO MVerb, a DPF'ied MVerb.
 * Copyright (c) 2010 Martin Eastwood
 * Copyright (C) 2014 Filipe Coelho <falktx@falktx.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * For a full copy of the GNU General Public License see the LICENSE file.
 */

#ifndef DISTRHO_UI_MVERB_HPP_INCLUDED
#define DISTRHO_UI_MVERB_HPP_INCLUDED

#include "DistrhoUI.hpp"
#include "ImageKnob.hpp"
#include "DistrhoArtworkMVerb.hpp"

#include <vector>

using DGL::Image;
using DGL::ImageKnob;

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class DistrhoUIMVerb : public UI,
                       public ImageKnob::Callback
{
public:
    DistrhoUIMVerb();
    ~DistrhoUIMVerb() override;

protected:
    // -------------------------------------------------------------------
    // Information

    uint d_getWidth() const noexcept override
    {
        return DistrhoArtworkMVerb::backgroundWidth;
    }

    uint d_getHeight() const noexcept override
    {
        return DistrhoArtworkMVerb::backgroundHeight;
    }

    // -------------------------------------------------------------------
    // DSP Callbacks

    void d_parameterChanged(uint32_t index, float value) override;
    void d_programChanged(uint32_t index) override;

    // -------------------------------------------------------------------
    // Widget Callbacks

    void imageKnobDragStarted(ImageKnob* knob) override;
    void imageKnobDragFinished(ImageKnob* knob) override;
    void imageKnobValueChanged(ImageKnob* knob, float value) override;

    void onDisplay() override;

private:
    Image fImgBackground;
    std::vector<ImageKnob*> fKnobs;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DistrhoUIMVerb)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // DISTRHO_UI_MVERB_HPP_INCLUDED
