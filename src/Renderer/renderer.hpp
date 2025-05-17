/**
 * @file renderer.hpp
 * @author Dante Harper
 * @date 16/05/25
 */

#pragma once

namespace renderer {
class TOAST_API OpenGL {
  void Init();
  void Resize(int width, int height);
  void BeginFrame();
  void RenderFrame(/*world context*/);
  void EndFrame();
  void Cleanup();
};
}
