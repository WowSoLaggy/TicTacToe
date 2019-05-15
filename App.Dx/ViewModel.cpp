#include "stdafx.h"
#include "ViewModel.h"

#include <LaggyDx/IRenderer2d.h>
#include <LaggyDx/IResourceController.h>


ViewModel::ViewModel(const Dx::IResourceController& i_resourceController)
  : d_resourceController(i_resourceController)
{
}


void ViewModel::createInitial()
{
  d_background = {
    d_resourceController.getResourceId("Grass.dds"),
    { 0, 0 },
    { 300, 100 }
  };
}


void ViewModel::render(Dx::IRenderer2d& i_renderer) const
{
  i_renderer.renderSprite(d_background);
}
