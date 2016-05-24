/*
 * File name: cairowinfake.cc
 * Date:      2007/08/21 21:32
 * Author:    Jan Faigl
 */

#include "cairowinfake.h"

using namespace imr::gui::cairo;

/// ----------------------------------------------------------------------------
/// Class CCairoWinFake
/// ----------------------------------------------------------------------------
CCairoWinFake::CCairoWinFake(CCanvasContainer * iCanvas) : CCairoWin(iCanvas) {
   width = 640;
   height = 480;
}

/// ----------------------------------------------------------------------------
CCairoWinFake::~CCairoWinFake() {
}

/// ----------------------------------------------------------------------------
void CCairoWinFake::initialize(void) {
   //nothing to do
}

/// ----------------------------------------------------------------------------
void CCairoWinFake::redraw(void) {
   //nothing to do
}

/// ----------------------------------------------------------------------------
void CCairoWinFake::invalidate(void) {
}

/// ----------------------------------------------------------------------------
void CCairoWinFake::start(void) {
   //nothing to do
}

/// ----------------------------------------------------------------------------
void CCairoWinFake::stop(void) {
   //nothing to do
}

/// ----------------------------------------------------------------------------
void CCairoWinFake::handleEvents(void) {
}

/// ----------------------------------------------------------------------------
void CCairoWinFake::setBackgroundColor(const SColor& color) {
   canvas->setBackgroundColor(color);
}


/* end of cairowinfake.cc */
