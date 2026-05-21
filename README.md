# Axion Engine — Roadmap

Progressive milestones for building Axion. Each phase produces a runnable, demonstrable result. Aligned with TheCherno's Hazel engine series so YouTube tutorials map directly to these tasks.

---

## ✅ Phase 0 — Foundation (DONE)

- [x] CMake + vcpkg build system
- [x] Engine library / Sandbox client separation
- [x] Precompiled headers
- [x] Logging system (spdlog wrapper, dual loggers)
- [x] Window abstraction (GLFW)
- [x] OpenGL 4.5 context (glad)
- [x] Application class with main loop
- [x] EntryPoint macro pattern
- [x] Smart pointer aliases (`Ref<T>`, `Scope<T>`)

**Deliverable:** Window opens, displays a clear color, logs to console.

---

## 🚧 Phase 1 — Event System

- [ ] `Event` base class with categories (Application, Input, Keyboard, Mouse)
- [ ] `EventDispatcher` for type-safe event handling
- [ ] Window events: `WindowCloseEvent`, `WindowResizeEvent`, `WindowFocusEvent`
- [ ] Key events: `KeyPressedEvent`, `KeyReleasedEvent`, `KeyTypedEvent`
- [ ] Mouse events: `MouseButtonPressedEvent`, `MouseMovedEvent`, `MouseScrolledEvent`
- [ ] Wire GLFW callbacks → push events into `Window` callback
- [ ] `Application::OnEvent()` receives events from window
- [ ] Add `KeyCode.h` / `MouseCode.h` (platform-agnostic input codes)

**Deliverable:** Pressing keys / clicking mouse logs events to console. Window resize updates viewport.

---

## 🚧 Phase 2 — Input Polling

- [ ] `Input` static class with `IsKeyPressed(KeyCode)`, `IsMouseButtonPressed`, `GetMousePosition`
- [ ] Platform-specific implementation (`WindowsInput.cpp` or single GLFW backend)

**Deliverable:** Move a debug variable with WASD, log mouse coords.

---

## 🚧 Phase 3 — Layer System

- [ ] `Layer` base class with `OnAttach`, `OnDetach`, `OnUpdate`, `OnEvent`, `OnImGuiRender`
- [ ] `LayerStack` (layers + overlays — overlays always on top)
- [ ] `Application` owns a `LayerStack`, iterates it each frame
- [ ] Events propagate top-to-bottom through layers (can be "handled" to stop)

**Deliverable:** Sandbox can push custom `ExampleLayer` that logs lifecycle events.

---

## 🚧 Phase 4 — ImGui Integration

- [ ] `ImGuiLayer` as an overlay
- [ ] ImGui GLFW + OpenGL3 backend bindings
- [ ] Begin/end frame in correct loop positions
- [ ] Docking enabled (vcpkg already configured for this)
- [ ] Demo window toggle

**Deliverable:** ImGui demo window renders over the OpenGL viewport. Foundation for future editor.

---

## 🚧 Phase 5 — Renderer Primitives (Triangle Era)

- [ ] `Shader` class (load from file, compile, uniform setters)
- [ ] `VertexBuffer` and `IndexBuffer` abstractions
- [ ] `BufferLayout` describing vertex attribute layout
- [ ] `VertexArray` (VAO wrapper)
- [ ] Render a colored triangle
- [ ] Render a square (with index buffer)

**Deliverable:** A rainbow triangle appears in the window. Foundational rite-of-passage.

---

## 🚧 Phase 6 — Renderer Abstraction

- [ ] `RendererAPI` abstract class (Clear, SetClearColor, DrawIndexed, SetViewport)
- [ ] `OpenGLRendererAPI` concrete implementation
- [ ] `RenderCommand` static dispatcher
- [ ] `Renderer` class with `BeginScene` / `Submit` / `EndScene`
- [ ] `OrthographicCamera` (position, rotation, projection matrix)

**Deliverable:** Camera moves with WASD. Scene structure works for multiple objects.

---

## 🚧 Phase 7 — Textures + 2D

- [ ] `Texture2D` abstract class
- [ ] `OpenGLTexture2D` using stb_image
- [ ] Texture units, binding, slot management
- [ ] Render a textured quad
- [ ] `OrthographicCameraController` (with zoom, aspect ratio, input handling)

**Deliverable:** Textured quad on screen, camera fully controllable.

---

## 🚧 Phase 8 — 2D Batch Renderer

- [ ] `Renderer2D::DrawQuad(position, size, color)`
- [ ] `Renderer2D::DrawQuad(position, size, texture)`
- [ ] Dynamic vertex buffer
- [ ] Batch many quads in one draw call
- [ ] Texture atlas support
- [ ] Stats: draw calls, quad count

**Deliverable:** Render 10,000 sprites at 60fps. Stress test confirms batching works.

---

## 🚧 Phase 9 — Entity Component System (ECS)

- [ ] Add `entt` to vcpkg
- [ ] `Scene` class wrapping `entt::registry`
- [ ] `Entity` wrapper class
- [ ] Core components: `TransformComponent`, `SpriteRendererComponent`, `CameraComponent`, `TagComponent`
- [ ] Scene rendering iterates entities with `TransformComponent` + `SpriteRendererComponent`
- [ ] Native scripting component (`NativeScriptComponent`)

**Deliverable:** Create entities, attach components, render them via scene.

---

## 🚧 Phase 10 — Editor (Axion-Editor)

- [ ] Spin off `Axion-Editor` executable (separate from Sandbox)
- [ ] Viewport panel (renders scene to framebuffer → ImGui image)
- [ ] Scene hierarchy panel
- [ ] Properties / inspector panel
- [ ] Content browser (file system view)
- [ ] Gizmos for transform manipulation (ImGuizmo)
- [ ] Entity selection, picking via mouse

**Deliverable:** A standalone editor that looks/feels like a real game engine editor. **HUGE portfolio piece.**

---

## 🚧 Phase 11 — Serialization

- [ ] Add `yaml-cpp` to vcpkg
- [ ] `SceneSerializer` — serialize scene to YAML
- [ ] Deserialize scene from YAML
- [ ] Editor: New Scene / Open Scene / Save / Save As menu
- [ ] File dialogs (native via Windows API)

**Deliverable:** Save a scene to disk, close editor, reopen, scene restored.

---

## 🚧 Phase 12 — Framebuffers / Render Targets

- [ ] `Framebuffer` abstraction (color + depth attachments)
- [ ] Scene renders to framebuffer instead of screen
- [ ] Viewport panel displays framebuffer texture
- [ ] Multiple render targets for post-processing later

**Deliverable:** Editor viewport shows the rendered scene as an ImGui image.

---

## 🚧 Phase 13 — Runtime / Editor split

- [ ] Scene play / stop / pause buttons in editor
- [ ] Runtime camera vs editor camera
- [ ] Scene copy on play (so changes during play don't persist)
- [ ] Native script binding (entity scripts run during play)

**Deliverable:** Editor + runtime distinction works like Unity.

---

## 🚧 Phase 14 — 3D Era

- [ ] `PerspectiveCamera` + controller
- [ ] Depth testing enabled
- [ ] Render a cube
- [ ] Mesh loading via Assimp (`.obj`, `.fbx`, `.gltf`)
- [ ] `MeshComponent`
- [ ] Basic Phong lighting shader

**Deliverable:** A 3D cube rotates in the editor viewport with directional lighting.

---

## 🚧 Phase 15 — Physics (2D first)

- [ ] Add `box2d` to vcpkg
- [ ] `Rigidbody2DComponent`, `BoxCollider2DComponent`, `CircleCollider2DComponent`
- [ ] Physics step in scene update
- [ ] Sync transforms between physics world and ECS

**Deliverable:** Drop boxes that fall and collide on play.

---

## 🚧 Phase 16+ — Beyond

Any of:
- Audio system (OpenAL Soft or miniaudio)
- Scripting layer (Lua via sol2, or C# via Mono)
- 3D physics (Jolt or Bullet)
- PBR shading
- Skeletal animation
- Particle system
- Networking
- Vulkan renderer backend
- Asset packing / hot reload

---

## Reference

- TheCherno's Hazel series: https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT
- Hazel source: https://github.com/TheCherno/Hazel
- Game Programming Patterns: https://gameprogrammingpatterns.com
- learnopengl.com (graphics fundamentals)

---