#ifndef SDL3PP_WINDOW_HPP
#define SDL3PP_WINDOW_HPP

#include <utility>
#include <string>
#include <string_view>


#include <SDL3/SDL_video.h>
#include <SDL3pp/movable_ptr.hpp>
#include <SDL3pp/observer_ptr.hpp>
#include <SDL3pp/Point.hpp>

namespace SDL3pp
{

using WindowFlags = SDL_WindowFlags;
using WindowID = SDL_WindowID;

class Window
{
public:
    /**
     * @brief Construct a new empty Window object
     * 
     * @warning don't create Window
     * object is not valid, necessite recall Constructor
     * 
     * Ex:
     * @code {.cpp}
     * SDL3pp::Window window; // Window object is not valid in this state
     * window = Window("Arch BTW", 500, 400);
     * @endcode
     * 
     * 
     */
    Window() = delete;

    /**
     * @brief Construct a new Window object
     * 
     * Create a window with the specified dimensions and flags.
     *
     * `flags` may be any of the following OR'd together:
     *
     * - `SDL_WINDOW_FULLSCREEN`: fullscreen window at desktop resolution
     * - `SDL_WINDOW_OPENGL`: window usable with an OpenGL context
     * - `SDL_WINDOW_OCCLUDED`: window partially or completely obscured by another
     *   window
     * - `SDL_WINDOW_HIDDEN`: window is not visible
     * - `SDL_WINDOW_BORDERLESS`: no window decoration
     * - `SDL_WINDOW_RESIZABLE`: window can be resized
     * - `SDL_WINDOW_MINIMIZED`: window is minimized
     * - `SDL_WINDOW_MAXIMIZED`: window is maximized
     * - `SDL_WINDOW_MOUSE_GRABBED`: window has grabbed mouse focus
     * - `SDL_WINDOW_INPUT_FOCUS`: window has input focus
     * - `SDL_WINDOW_MOUSE_FOCUS`: window has mouse focus
     * - `SDL_WINDOW_EXTERNAL`: window not created by SDL
     * - `SDL_WINDOW_MODAL`: window is modal
     * - `SDL_WINDOW_HIGH_PIXEL_DENSITY`: window uses high pixel density back
     *   buffer if possible
     * - `SDL_WINDOW_MOUSE_CAPTURE`: window has mouse captured (unrelated to
     *   MOUSE_GRABBED)
     * - `SDL_WINDOW_ALWAYS_ON_TOP`: window should always be above others
     * - `SDL_WINDOW_UTILITY`: window should be treated as a utility window, not
     *   showing in the task bar and window list
     * - `SDL_WINDOW_TOOLTIP`: window should be treated as a tooltip and does not
     *   get mouse or keyboard focus, requires a parent window
     * - `SDL_WINDOW_POPUP_MENU`: window should be treated as a popup menu,
     *   requires a parent window
     * - `SDL_WINDOW_KEYBOARD_GRABBED`: window has grabbed keyboard input
     * - `SDL_WINDOW_VULKAN`: window usable with a Vulkan instance
     * - `SDL_WINDOW_METAL`: window usable with a Metal instance
     * - `SDL_WINDOW_TRANSPARENT`: window with transparent buffer
     * - `SDL_WINDOW_NOT_FOCUSABLE`: window should not be focusable
     *
     * The SDL3pp::Window is implicitly shown if SDL_WINDOW_HIDDEN is not set.
     *
     * On Apple's macOS, you **must** set the NSHighResolutionCapable Info.plist
     * property to YES, otherwise you will not receive a High-DPI OpenGL canvas.
     *
     * The window pixel size may differ from its window coordinate size if the
     * window is on a high pixel density display. Use SDL_GetWindowSize() to query
     * the client area's size in window coordinates, and
     * SDL_GetWindowSizeInPixels() or SDL_GetRenderOutputSize() to query the
     * drawable size in pixels. Note that the drawable size can vary after the
     * window is created and should be queried again if you get an
     * SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED event.
     *
     * 
     * @todo changer les noms de fonction dans la doc
     * 
     * If the window is created with any of the SDL_WINDOW_OPENGL or
     * SDL_WINDOW_VULKAN flags, then the corresponding LoadLibrary function
     * (SDL_GL_LoadLibrary or SDL_Vulkan_LoadLibrary) is called and the
     * corresponding UnloadLibrary function is called by destructor.
     *
     * If SDL_WINDOW_VULKAN is specified and there isn't a working Vulkan driver,
     * constructor will fail, because SDL_Vulkan_LoadLibrary() will fail.
     *
     * If SDL_WINDOW_METAL is specified on an OS that does not support Metal,
     * constructor will fail.
     *
     * If you intend to use this window with an SDL3pp::renderer, you should use
     * SDL3pp::CreateWindowAndRenderer() instead of this function, to avoid window
     * flicker.
     *
     * On non-Apple devices, SDL requires you to either not link to the Vulkan
     * loader or link to a dynamic library version. This limitation may be removed
     * in a future version of SDL.
     *
     * @param title the title of the window, in UTF-8 encoding.
     * @param w the width of the window.
     * @param h the height of the window.
     * @param flags 0, or one or more SDL_WindowFlags OR'd together.
     * @returns the window that was created or NULL on failure; 
     * 
     * @exception SDL3pp::exception call exception.what() for more information about this
     *
     * @threadsafety This function should only be called on the main thread.
     *
     * @since This function is available since SDL 3.2.0.
     */
    Window(std::string const& title, int w, int h, WindowFlags flags = 0);
    
    Window(Window& parent, int offset_x, int offset_y, int w, int h, WindowFlags flags);

    inline Window(SDL_Window* window);

    /**
     * @todo Implémenter le constructeur prenant un SDL_Propirties
     */

    Window(Window const&) = delete;
    Window& operator=(Window const&) = delete;

    Window(Window&&) = default;
    Window& operator=(Window&&);

    virtual ~Window();

    inline std::pair<int, int> get_size() const;

    inline int get_width() const;

    inline int get_height() const;

    inline std::pair<int, int> get_size_in_pixel() const;

    inline int get_width_in_pixel() const;

    inline int get_height_in_pixel() const;

    inline std::string_view get_title() const;

    inline void set_title(std::string const& title);

    inline observer_ptr<Window> get_parent() const;

    inline void set_parent(Window& parent);

    inline Point get_position() const;

private:
    movable_ptr<SDL_Window> m_window;
    observer_ptr<Window> m_parent_window;
};

} // namespace SDL3pp

#include "inline_src/Window.inl"
#endif