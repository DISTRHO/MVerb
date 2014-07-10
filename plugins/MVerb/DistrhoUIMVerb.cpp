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

#include "DistrhoUIMVerb.hpp"
#include "MVerb.h"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

DistrhoUIMVerb::DistrhoUIMVerb()
    : UI()
{
    // background
    fImgBackground = Image(DistrhoArtworkMVerb::backgroundData, DistrhoArtworkMVerb::backgroundWidth, DistrhoArtworkMVerb::backgroundHeight, GL_BGR);

    // knobs
    Image knobImage(DistrhoArtworkMVerb::knobData, DistrhoArtworkMVerb::knobWidth, DistrhoArtworkMVerb::knobHeight);

    // the knobs on the UI don't follow the parameter order
    for (int i=0; i<MVerb<float>::NUM_PARAMS; ++i)
        fKnobs.push_back(nullptr);

    for (int i=0; i<MVerb<float>::NUM_PARAMS; ++i)
    {
        int x = 0;
        switch (i)
        {
        case MVerb<float>::DAMPINGFREQ:
            x = 7;
            break;
        case MVerb<float>::DENSITY:
            x = 4;
            break;
        case MVerb<float>::BANDWIDTHFREQ:
            x = 5;
            break;
        case MVerb<float>::DECAY:
            x = 6;
            break;
        case MVerb<float>::PREDELAY:
            x = 1;
            break;
        case MVerb<float>::SIZE:
            x = 3;
            break;
        case MVerb<float>::GAIN:
            x = 8;
            break;
        case MVerb<float>::MIX:
            x = 0;
            break;
        case MVerb<float>::EARLYMIX:
            x = 2;
            break;
        }

        ImageKnob* const knob(new ImageKnob(this, knobImage, ImageKnob::Vertical, i));
        knob->setAbsolutePos(56 + x*40, 40);
        knob->setRange(0.0f, 100.0f);
        knob->setDefault(50.0f);
        knob->setRotationAngle(270);
        knob->setCallback(this);

        fKnobs[i] = knob;
    }

    fKnobs[MVerb<float>::GAIN]->setDefault(75.0f);
    fKnobs[MVerb<float>::SIZE]->setDefault(100.0f);

    // set initial values
    d_programChanged(0);
}

DistrhoUIMVerb::~DistrhoUIMVerb()
{
    for (std::vector<ImageKnob*>::iterator it=fKnobs.begin(), end=fKnobs.end(); it != end; ++it)
    {
        ImageKnob* const knob(*it);
        delete knob;
    }

    fKnobs.clear();
}

// -----------------------------------------------------------------------
// DSP Callbacks

void DistrhoUIMVerb::d_parameterChanged(uint32_t index, float value)
{
    fKnobs[index]->setValue(value);
}

void DistrhoUIMVerb::d_programChanged(uint32_t index)
{
    switch(index)
    {
    case 0:
        fKnobs[MVerb<float>::DAMPINGFREQ]->setValue(0.5f*100.0f);
        fKnobs[MVerb<float>::DENSITY]->setValue(0.5f*100.0f);
        fKnobs[MVerb<float>::BANDWIDTHFREQ]->setValue(0.5f*100.0f);
        fKnobs[MVerb<float>::DECAY]->setValue(0.5f*100.0f);
        fKnobs[MVerb<float>::PREDELAY]->setValue(0.5f*100.0f);
        fKnobs[MVerb<float>::GAIN]->setValue(1.0f*100.0f);
        fKnobs[MVerb<float>::MIX]->setValue(0.5f*100.0f);
        fKnobs[MVerb<float>::EARLYMIX]->setValue(0.5f*100.0f);
        fKnobs[MVerb<float>::SIZE]->setValue(0.75f*100.0f);
        break;
    case 1:
        fKnobs[MVerb<float>::DAMPINGFREQ]->setValue(0.9f*100.0f);
        fKnobs[MVerb<float>::DENSITY]->setValue(0.5f*100.0f);
        fKnobs[MVerb<float>::BANDWIDTHFREQ]->setValue(0.1f*100.0f);
        fKnobs[MVerb<float>::DECAY]->setValue(0.5f*100.0f);
        fKnobs[MVerb<float>::PREDELAY]->setValue(0.0f*100.0f);
        fKnobs[MVerb<float>::SIZE]->setValue(0.5f*100.0f);
        fKnobs[MVerb<float>::GAIN]->setValue(1.0f*100.0f);
        fKnobs[MVerb<float>::MIX]->setValue(0.5f*100.0f);
        fKnobs[MVerb<float>::EARLYMIX]->setValue(0.75f*100.0f);
        break;
    case 2:
        fKnobs[MVerb<float>::DAMPINGFREQ]->setValue(0.0f*100.0f);
        fKnobs[MVerb<float>::DENSITY]->setValue(0.5f*100.0f);
        fKnobs[MVerb<float>::BANDWIDTHFREQ]->setValue(1.0f*100.0f);
        fKnobs[MVerb<float>::DECAY]->setValue(0.5f*100.0f);
        fKnobs[MVerb<float>::PREDELAY]->setValue(0.0f*100.0f);
        fKnobs[MVerb<float>::SIZE]->setValue(0.25f*100.0f);
        fKnobs[MVerb<float>::GAIN]->setValue(1.0f*100.0f);
        fKnobs[MVerb<float>::MIX]->setValue(0.35f*100.0f);
        fKnobs[MVerb<float>::EARLYMIX]->setValue(0.75f*100.0f);
        break;
    case 3:
        fKnobs[MVerb<float>::DAMPINGFREQ]->setValue(0.0f*100.0f);
        fKnobs[MVerb<float>::DENSITY]->setValue(0.5f*100.0f);
        fKnobs[MVerb<float>::BANDWIDTHFREQ]->setValue(1.0f*100.0f);
        fKnobs[MVerb<float>::DECAY]->setValue(0.5f*100.0f);
        fKnobs[MVerb<float>::PREDELAY]->setValue(0.0f*100.0f);
        fKnobs[MVerb<float>::SIZE]->setValue(1.0f*100.0f);
        fKnobs[MVerb<float>::GAIN]->setValue(1.0f*100.0f);
        fKnobs[MVerb<float>::MIX]->setValue(0.35f*100.0f);
        fKnobs[MVerb<float>::EARLYMIX]->setValue(0.75f*100.0f);
        break;
    case 4:
        fKnobs[MVerb<float>::DAMPINGFREQ]->setValue(0.0f*100.0f);
        fKnobs[MVerb<float>::DENSITY]->setValue(0.5f*100.0f);
        fKnobs[MVerb<float>::BANDWIDTHFREQ]->setValue(1.0f*100.0f);
        fKnobs[MVerb<float>::DECAY]->setValue(0.5f*100.0f);
        fKnobs[MVerb<float>::PREDELAY]->setValue(0.0f*100.0f);
        fKnobs[MVerb<float>::SIZE]->setValue(0.5f*100.0f);
        fKnobs[MVerb<float>::GAIN]->setValue(1.0f*100.0f);
        fKnobs[MVerb<float>::MIX]->setValue(0.15f*100.0f);
        fKnobs[MVerb<float>::EARLYMIX]->setValue(0.75f*100.0f);
        break;
    }
}

// -----------------------------------------------------------------------
// Widget Callbacks

void DistrhoUIMVerb::imageKnobDragStarted(ImageKnob* knob)
{
    d_editParameter(knob->getId(), true);
}

void DistrhoUIMVerb::imageKnobDragFinished(ImageKnob* knob)
{
    d_editParameter(knob->getId(), false);
}

void DistrhoUIMVerb::imageKnobValueChanged(ImageKnob* knob, float value)
{
    d_setParameterValue(knob->getId(), value);
}

void DistrhoUIMVerb::onDisplay()
{
    fImgBackground.draw();
}

// -----------------------------------------------------------------------

UI* createUI()
{
    return new DistrhoUIMVerb();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
