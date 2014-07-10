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

#include "font/Kh-Kangrey.h"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

static int getKnobPosInUI(const int index)
{
    switch (index)
    {
    case MVerb<float>::DAMPINGFREQ:
        return 7;
    case MVerb<float>::DENSITY:
        return 4;
    case MVerb<float>::BANDWIDTHFREQ:
        return 5;
    case MVerb<float>::DECAY:
        return 6;
    case MVerb<float>::PREDELAY:
        return 1;
    case MVerb<float>::SIZE:
        return 3;
    case MVerb<float>::GAIN:
        return 8;
    case MVerb<float>::MIX:
        return 0;
    case MVerb<float>::EARLYMIX:
        return 2;
    default:
        return 0;
    }
}
DistrhoUIMVerb::DistrhoUIMVerb()
    : UI()
{
    // background
    fImgBackground = Image(DistrhoArtworkMVerb::backgroundData, DistrhoArtworkMVerb::backgroundWidth, DistrhoArtworkMVerb::backgroundHeight, GL_BGR);

    // text
    fNanoText.createFontMem("kh", (uchar*)khkangrey_ttf, khkangrey_ttfSize, false);

    // knobs
    Image knobImage(DistrhoArtworkMVerb::knobData, DistrhoArtworkMVerb::knobWidth, DistrhoArtworkMVerb::knobHeight);

    // the knobs on the UI don't follow the parameter order
    for (int i=0; i<MVerb<float>::NUM_PARAMS; ++i)
        fKnobs.push_back(nullptr);

    for (int i=0; i<MVerb<float>::NUM_PARAMS; ++i)
    {
        const int x(getKnobPosInUI(i));
        ImageKnob* const knob(new ImageKnob(this, knobImage, ImageKnob::Vertical, i));
        knob->setAbsolutePos(56 + x*40, 40);
        knob->setRange(0.0f, 100.0f);
        knob->setDefault(50.0f);
        knob->setCallback(this);

        fKnobs[i] = knob;
    }

    fKnobs[MVerb<float>::GAIN]->setDefault(75.0f);
    fKnobs[MVerb<float>::SIZE]->setRange(5.0f, 100.0f);
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

    // text display
    fNanoText.beginFrame(getWidth(), getHeight());

    fNanoText.fontFace("kh");
    fNanoText.fontSize(20);
    fNanoText.textAlign(NanoVG::Align(NanoVG::ALIGN_CENTER|NanoVG::ALIGN_TOP));
    fNanoText.fillColor(NanoVG::RGBf(1.0f, 1.0f, 1.0f));

    char strBuf[32+1];
    strBuf[32] = '\0';

    for (int i=0; i<MVerb<float>::NUM_PARAMS; ++i)
    {
        const int x(getKnobPosInUI(i));
        std::snprintf(strBuf, 32, "%i%%", int(fKnobs[i]->getValue()));
        fNanoText.textBox(58 + x*40, 73, 30.0f, strBuf, nullptr);
    }

    fNanoText.endFrame();

    // just in case
    glDisable(GL_CULL_FACE);
}

// -----------------------------------------------------------------------

UI* createUI()
{
    return new DistrhoUIMVerb();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
