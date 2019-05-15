#pragma once

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggyDx/Sprite.h>


class ViewModel
{
public:
  ViewModel(const Dx::IResourceController& i_resourceController);

  void createInitial();

  void render(Dx::IRenderer2d& i_renderer) const;

private:
  const Dx::IResourceController& d_resourceController;

  Dx::Sprite d_background;
  Dx::Sprite d_field;
};
