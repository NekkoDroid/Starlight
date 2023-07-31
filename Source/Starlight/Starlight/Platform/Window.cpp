#include "Window.hpp"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_video.h>

#include <array>
#include <utility>

namespace
{
	using namespace Star;

	[[nodiscard]] auto MakeWindow(const char* title, glm::ivec2 size, uint32_t flags) -> SDLPointer<SDL_Window>
	{
		static constexpr auto posX = SDL_WINDOWPOS_UNDEFINED;
		static constexpr auto posY = SDL_WINDOWPOS_UNDEFINED;

		if (auto* window = SDL_CreateWindow(title, posX, posY, size.x, size.y, flags))
			return SDLPointer<SDL_Window>{window};

		throw WindowException{SDL_GetError()};
	}

	constexpr auto WindowDataKey = "1fbb532a-1b2a-11ed-861d-0242ac120002";

	[[nodiscard]] auto GetCurrentWindow(uint32_t windowId) -> Window*
	{
		if (auto* window = SDL_GetWindowFromID(windowId))
			return static_cast<Window*>(SDL_GetWindowData(window, WindowDataKey));

		throw WindowException{SDL_GetError()};
	}
} //namespace

namespace Star
{
	auto SDLDeleter::operator()(SDL_Window* ptr) const noexcept -> void
	{
		SDL_DestroyWindow(ptr);
	}

	Window::Window(const char* title, glm::ivec2 size, uint32_t flags) :
		m_Window{MakeWindow(title, size, flags)}
	{
		SDL_SetWindowData(Handle(), WindowDataKey, this);
	}

	Window::Window(Window&& other) noexcept :
		m_Window{std::move(other.m_Window)},
		m_WindowListener{std::exchange(other.m_WindowListener, nullptr)},
		m_InputListener{std::exchange(other.m_InputListener, nullptr)},
		m_TextListener{std::exchange(other.m_TextListener, nullptr)}
	{
		SDL_SetWindowData(Handle(), WindowDataKey, this);
	}

	auto Window::operator=(Window&& other) noexcept -> Window&
	{
		if (std::addressof(other) != this)
		{
			m_Window = std::move(other.m_Window);
			m_WindowListener = std::exchange(other.m_WindowListener, nullptr);
			m_InputListener = std::exchange(other.m_InputListener, nullptr);
			m_TextListener = std::exchange(other.m_TextListener, nullptr);
			SDL_SetWindowData(Handle(), WindowDataKey, this);
		}

		return *this;
	}

	auto Window::HandleEvent(const SDL_WindowEvent& event) -> void
	{
		auto* self = GetCurrentWindow(event.windowID);

		switch (event.event)
		{
		case SDL_WINDOWEVENT_CLOSE:
			self->OnEvent(WindowCloseEventArgs{});
			break;

		case SDL_WINDOWEVENT_SIZE_CHANGED:
		{
			auto* window = self->Handle();

			WindowResizeEventArgs args{};
			SDL_GetWindowSize(window, &args.Size.x, &args.Size.y);
			SDL_GetWindowSizeInPixels(window, &args.Pixel.x, &args.Pixel.y);

			self->OnEvent(args);
			break;
		}
		case SDL_WINDOWEVENT_ENTER:
			self->OnEvent(MouseFocusChancedEventArgs{
				.Focused = true,
			});
			break;

		case SDL_WINDOWEVENT_LEAVE:
			self->OnEvent(MouseFocusChancedEventArgs{
				.Focused = false,
			});
			break;

		case SDL_WINDOWEVENT_FOCUS_GAINED:
			self->OnEvent(KeyboardFocusChancedEventArgs{
				.Focused = true,
			});
			break;

		case SDL_WINDOWEVENT_FOCUS_LOST:
			self->OnEvent(KeyboardFocusChancedEventArgs{
				.Focused = false,
			});
			break;
		}
	}

	auto Window::HandleEvent(const SDL_KeyboardEvent& event) -> void
	{
		auto* self = GetCurrentWindow(event.windowID);

		static_assert(static_cast<SDL_Scancode>(Key::Unknown) == SDL_SCANCODE_UNKNOWN);
		static_assert(static_cast<SDL_Scancode>(Key::A) == SDL_SCANCODE_A);
		static_assert(static_cast<SDL_Scancode>(Key::B) == SDL_SCANCODE_B);
		static_assert(static_cast<SDL_Scancode>(Key::C) == SDL_SCANCODE_C);
		static_assert(static_cast<SDL_Scancode>(Key::D) == SDL_SCANCODE_D);
		static_assert(static_cast<SDL_Scancode>(Key::E) == SDL_SCANCODE_E);
		static_assert(static_cast<SDL_Scancode>(Key::F) == SDL_SCANCODE_F);
		static_assert(static_cast<SDL_Scancode>(Key::G) == SDL_SCANCODE_G);
		static_assert(static_cast<SDL_Scancode>(Key::H) == SDL_SCANCODE_H);
		static_assert(static_cast<SDL_Scancode>(Key::I) == SDL_SCANCODE_I);
		static_assert(static_cast<SDL_Scancode>(Key::J) == SDL_SCANCODE_J);
		static_assert(static_cast<SDL_Scancode>(Key::K) == SDL_SCANCODE_K);
		static_assert(static_cast<SDL_Scancode>(Key::L) == SDL_SCANCODE_L);
		static_assert(static_cast<SDL_Scancode>(Key::M) == SDL_SCANCODE_M);
		static_assert(static_cast<SDL_Scancode>(Key::N) == SDL_SCANCODE_N);
		static_assert(static_cast<SDL_Scancode>(Key::O) == SDL_SCANCODE_O);
		static_assert(static_cast<SDL_Scancode>(Key::P) == SDL_SCANCODE_P);
		static_assert(static_cast<SDL_Scancode>(Key::Q) == SDL_SCANCODE_Q);
		static_assert(static_cast<SDL_Scancode>(Key::R) == SDL_SCANCODE_R);
		static_assert(static_cast<SDL_Scancode>(Key::S) == SDL_SCANCODE_S);
		static_assert(static_cast<SDL_Scancode>(Key::T) == SDL_SCANCODE_T);
		static_assert(static_cast<SDL_Scancode>(Key::U) == SDL_SCANCODE_U);
		static_assert(static_cast<SDL_Scancode>(Key::V) == SDL_SCANCODE_V);
		static_assert(static_cast<SDL_Scancode>(Key::W) == SDL_SCANCODE_W);
		static_assert(static_cast<SDL_Scancode>(Key::X) == SDL_SCANCODE_X);
		static_assert(static_cast<SDL_Scancode>(Key::Y) == SDL_SCANCODE_Y);
		static_assert(static_cast<SDL_Scancode>(Key::Z) == SDL_SCANCODE_Z);
		static_assert(static_cast<SDL_Scancode>(Key::Nr1) == SDL_SCANCODE_1);
		static_assert(static_cast<SDL_Scancode>(Key::Nr2) == SDL_SCANCODE_2);
		static_assert(static_cast<SDL_Scancode>(Key::Nr3) == SDL_SCANCODE_3);
		static_assert(static_cast<SDL_Scancode>(Key::Nr4) == SDL_SCANCODE_4);
		static_assert(static_cast<SDL_Scancode>(Key::Nr5) == SDL_SCANCODE_5);
		static_assert(static_cast<SDL_Scancode>(Key::Nr6) == SDL_SCANCODE_6);
		static_assert(static_cast<SDL_Scancode>(Key::Nr7) == SDL_SCANCODE_7);
		static_assert(static_cast<SDL_Scancode>(Key::Nr8) == SDL_SCANCODE_8);
		static_assert(static_cast<SDL_Scancode>(Key::Nr9) == SDL_SCANCODE_9);
		static_assert(static_cast<SDL_Scancode>(Key::Nr0) == SDL_SCANCODE_0);
		static_assert(static_cast<SDL_Scancode>(Key::Nr0) == SDL_SCANCODE_0);
		static_assert(static_cast<SDL_Scancode>(Key::Return) == SDL_SCANCODE_RETURN);
		static_assert(static_cast<SDL_Scancode>(Key::Escape) == SDL_SCANCODE_ESCAPE);
		static_assert(static_cast<SDL_Scancode>(Key::Backspace) == SDL_SCANCODE_BACKSPACE);
		static_assert(static_cast<SDL_Scancode>(Key::Tab) == SDL_SCANCODE_TAB);
		static_assert(static_cast<SDL_Scancode>(Key::Space) == SDL_SCANCODE_SPACE);
		static_assert(static_cast<SDL_Scancode>(Key::Minus) == SDL_SCANCODE_MINUS);
		static_assert(static_cast<SDL_Scancode>(Key::Equals) == SDL_SCANCODE_EQUALS);
		static_assert(static_cast<SDL_Scancode>(Key::LeftBracket) == SDL_SCANCODE_LEFTBRACKET);
		static_assert(static_cast<SDL_Scancode>(Key::RightBracket) == SDL_SCANCODE_RIGHTBRACKET);
		static_assert(static_cast<SDL_Scancode>(Key::Backslash) == SDL_SCANCODE_BACKSLASH);
		static_assert(static_cast<SDL_Scancode>(Key::NonUSHash) == SDL_SCANCODE_NONUSHASH);
		static_assert(static_cast<SDL_Scancode>(Key::Semicolon) == SDL_SCANCODE_SEMICOLON);
		static_assert(static_cast<SDL_Scancode>(Key::Apostrophe) == SDL_SCANCODE_APOSTROPHE);
		static_assert(static_cast<SDL_Scancode>(Key::Grave) == SDL_SCANCODE_GRAVE);
		static_assert(static_cast<SDL_Scancode>(Key::Comma) == SDL_SCANCODE_COMMA);
		static_assert(static_cast<SDL_Scancode>(Key::Period) == SDL_SCANCODE_PERIOD);
		static_assert(static_cast<SDL_Scancode>(Key::Slash) == SDL_SCANCODE_SLASH);
		static_assert(static_cast<SDL_Scancode>(Key::CapsLock) == SDL_SCANCODE_CAPSLOCK);
		static_assert(static_cast<SDL_Scancode>(Key::F1) == SDL_SCANCODE_F1);
		static_assert(static_cast<SDL_Scancode>(Key::F2) == SDL_SCANCODE_F2);
		static_assert(static_cast<SDL_Scancode>(Key::F3) == SDL_SCANCODE_F3);
		static_assert(static_cast<SDL_Scancode>(Key::F4) == SDL_SCANCODE_F4);
		static_assert(static_cast<SDL_Scancode>(Key::F5) == SDL_SCANCODE_F5);
		static_assert(static_cast<SDL_Scancode>(Key::F6) == SDL_SCANCODE_F6);
		static_assert(static_cast<SDL_Scancode>(Key::F7) == SDL_SCANCODE_F7);
		static_assert(static_cast<SDL_Scancode>(Key::F8) == SDL_SCANCODE_F8);
		static_assert(static_cast<SDL_Scancode>(Key::F9) == SDL_SCANCODE_F9);
		static_assert(static_cast<SDL_Scancode>(Key::F10) == SDL_SCANCODE_F10);
		static_assert(static_cast<SDL_Scancode>(Key::F11) == SDL_SCANCODE_F11);
		static_assert(static_cast<SDL_Scancode>(Key::F12) == SDL_SCANCODE_F12);
		static_assert(static_cast<SDL_Scancode>(Key::PrintScreen) == SDL_SCANCODE_PRINTSCREEN);
		static_assert(static_cast<SDL_Scancode>(Key::ScrollLock) == SDL_SCANCODE_SCROLLLOCK);
		static_assert(static_cast<SDL_Scancode>(Key::Pause) == SDL_SCANCODE_PAUSE);
		static_assert(static_cast<SDL_Scancode>(Key::Insert) == SDL_SCANCODE_INSERT);
		static_assert(static_cast<SDL_Scancode>(Key::Home) == SDL_SCANCODE_HOME);
		static_assert(static_cast<SDL_Scancode>(Key::PageUp) == SDL_SCANCODE_PAGEUP);
		static_assert(static_cast<SDL_Scancode>(Key::Delete) == SDL_SCANCODE_DELETE);
		static_assert(static_cast<SDL_Scancode>(Key::End) == SDL_SCANCODE_END);
		static_assert(static_cast<SDL_Scancode>(Key::PageDown) == SDL_SCANCODE_PAGEDOWN);
		static_assert(static_cast<SDL_Scancode>(Key::Right) == SDL_SCANCODE_RIGHT);
		static_assert(static_cast<SDL_Scancode>(Key::Left) == SDL_SCANCODE_LEFT);
		static_assert(static_cast<SDL_Scancode>(Key::Down) == SDL_SCANCODE_DOWN);
		static_assert(static_cast<SDL_Scancode>(Key::Up) == SDL_SCANCODE_UP);
		static_assert(static_cast<SDL_Scancode>(Key::NumLock) == SDL_SCANCODE_NUMLOCKCLEAR);
		static_assert(static_cast<SDL_Scancode>(Key::KpDivide) == SDL_SCANCODE_KP_DIVIDE);
		static_assert(static_cast<SDL_Scancode>(Key::KpMultiply) == SDL_SCANCODE_KP_MULTIPLY);
		static_assert(static_cast<SDL_Scancode>(Key::KpMinus) == SDL_SCANCODE_KP_MINUS);
		static_assert(static_cast<SDL_Scancode>(Key::KpPlus) == SDL_SCANCODE_KP_PLUS);
		static_assert(static_cast<SDL_Scancode>(Key::KpEnter) == SDL_SCANCODE_KP_ENTER);
		static_assert(static_cast<SDL_Scancode>(Key::Kp1) == SDL_SCANCODE_KP_1);
		static_assert(static_cast<SDL_Scancode>(Key::Kp2) == SDL_SCANCODE_KP_2);
		static_assert(static_cast<SDL_Scancode>(Key::Kp3) == SDL_SCANCODE_KP_3);
		static_assert(static_cast<SDL_Scancode>(Key::Kp4) == SDL_SCANCODE_KP_4);
		static_assert(static_cast<SDL_Scancode>(Key::Kp5) == SDL_SCANCODE_KP_5);
		static_assert(static_cast<SDL_Scancode>(Key::Kp6) == SDL_SCANCODE_KP_6);
		static_assert(static_cast<SDL_Scancode>(Key::Kp7) == SDL_SCANCODE_KP_7);
		static_assert(static_cast<SDL_Scancode>(Key::Kp8) == SDL_SCANCODE_KP_8);
		static_assert(static_cast<SDL_Scancode>(Key::Kp9) == SDL_SCANCODE_KP_9);
		static_assert(static_cast<SDL_Scancode>(Key::Kp0) == SDL_SCANCODE_KP_0);
		static_assert(static_cast<SDL_Scancode>(Key::KpPeriod) == SDL_SCANCODE_KP_PERIOD);
		static_assert(static_cast<SDL_Scancode>(Key::NonUSBackslash) == SDL_SCANCODE_NONUSBACKSLASH);
		static_assert(static_cast<SDL_Scancode>(Key::Application) == SDL_SCANCODE_APPLICATION);
		static_assert(static_cast<SDL_Scancode>(Key::Power) == SDL_SCANCODE_POWER);
		static_assert(static_cast<SDL_Scancode>(Key::KpEquals) == SDL_SCANCODE_KP_EQUALS);
		static_assert(static_cast<SDL_Scancode>(Key::F13) == SDL_SCANCODE_F13);
		static_assert(static_cast<SDL_Scancode>(Key::F14) == SDL_SCANCODE_F14);
		static_assert(static_cast<SDL_Scancode>(Key::F15) == SDL_SCANCODE_F15);
		static_assert(static_cast<SDL_Scancode>(Key::F16) == SDL_SCANCODE_F16);
		static_assert(static_cast<SDL_Scancode>(Key::F17) == SDL_SCANCODE_F17);
		static_assert(static_cast<SDL_Scancode>(Key::F18) == SDL_SCANCODE_F18);
		static_assert(static_cast<SDL_Scancode>(Key::F19) == SDL_SCANCODE_F19);
		static_assert(static_cast<SDL_Scancode>(Key::F20) == SDL_SCANCODE_F20);
		static_assert(static_cast<SDL_Scancode>(Key::F21) == SDL_SCANCODE_F21);
		static_assert(static_cast<SDL_Scancode>(Key::F22) == SDL_SCANCODE_F22);
		static_assert(static_cast<SDL_Scancode>(Key::F23) == SDL_SCANCODE_F23);
		static_assert(static_cast<SDL_Scancode>(Key::F24) == SDL_SCANCODE_F24);
		static_assert(static_cast<SDL_Scancode>(Key::Execute) == SDL_SCANCODE_EXECUTE);
		static_assert(static_cast<SDL_Scancode>(Key::Help) == SDL_SCANCODE_HELP);
		static_assert(static_cast<SDL_Scancode>(Key::Menu) == SDL_SCANCODE_MENU);
		static_assert(static_cast<SDL_Scancode>(Key::Select) == SDL_SCANCODE_SELECT);
		static_assert(static_cast<SDL_Scancode>(Key::Stop) == SDL_SCANCODE_STOP);
		static_assert(static_cast<SDL_Scancode>(Key::Redo) == SDL_SCANCODE_AGAIN);
		static_assert(static_cast<SDL_Scancode>(Key::Undo) == SDL_SCANCODE_UNDO);
		static_assert(static_cast<SDL_Scancode>(Key::Cut) == SDL_SCANCODE_CUT);
		static_assert(static_cast<SDL_Scancode>(Key::Copy) == SDL_SCANCODE_COPY);
		static_assert(static_cast<SDL_Scancode>(Key::Paste) == SDL_SCANCODE_PASTE);
		static_assert(static_cast<SDL_Scancode>(Key::Find) == SDL_SCANCODE_FIND);
		static_assert(static_cast<SDL_Scancode>(Key::Mute) == SDL_SCANCODE_MUTE);
		static_assert(static_cast<SDL_Scancode>(Key::VolumeUp) == SDL_SCANCODE_VOLUMEUP);
		static_assert(static_cast<SDL_Scancode>(Key::VolumeDown) == SDL_SCANCODE_VOLUMEDOWN);
		static_assert(static_cast<SDL_Scancode>(Key::KpComma) == SDL_SCANCODE_KP_COMMA);
		static_assert(static_cast<SDL_Scancode>(Key::KpEqualsAs400) == SDL_SCANCODE_KP_EQUALSAS400);
		static_assert(static_cast<SDL_Scancode>(Key::International1) == SDL_SCANCODE_INTERNATIONAL1);
		static_assert(static_cast<SDL_Scancode>(Key::International2) == SDL_SCANCODE_INTERNATIONAL2);
		static_assert(static_cast<SDL_Scancode>(Key::International3) == SDL_SCANCODE_INTERNATIONAL3);
		static_assert(static_cast<SDL_Scancode>(Key::International4) == SDL_SCANCODE_INTERNATIONAL4);
		static_assert(static_cast<SDL_Scancode>(Key::International5) == SDL_SCANCODE_INTERNATIONAL5);
		static_assert(static_cast<SDL_Scancode>(Key::International6) == SDL_SCANCODE_INTERNATIONAL6);
		static_assert(static_cast<SDL_Scancode>(Key::International7) == SDL_SCANCODE_INTERNATIONAL7);
		static_assert(static_cast<SDL_Scancode>(Key::International8) == SDL_SCANCODE_INTERNATIONAL8);
		static_assert(static_cast<SDL_Scancode>(Key::International9) == SDL_SCANCODE_INTERNATIONAL9);
		static_assert(static_cast<SDL_Scancode>(Key::Lang1) == SDL_SCANCODE_LANG1);
		static_assert(static_cast<SDL_Scancode>(Key::Lang2) == SDL_SCANCODE_LANG2);
		static_assert(static_cast<SDL_Scancode>(Key::Lang3) == SDL_SCANCODE_LANG3);
		static_assert(static_cast<SDL_Scancode>(Key::Lang4) == SDL_SCANCODE_LANG4);
		static_assert(static_cast<SDL_Scancode>(Key::Lang5) == SDL_SCANCODE_LANG5);
		static_assert(static_cast<SDL_Scancode>(Key::Lang6) == SDL_SCANCODE_LANG6);
		static_assert(static_cast<SDL_Scancode>(Key::Lang7) == SDL_SCANCODE_LANG7);
		static_assert(static_cast<SDL_Scancode>(Key::Lang8) == SDL_SCANCODE_LANG8);
		static_assert(static_cast<SDL_Scancode>(Key::Lang9) == SDL_SCANCODE_LANG9);
		static_assert(static_cast<SDL_Scancode>(Key::AltErase) == SDL_SCANCODE_ALTERASE);
		static_assert(static_cast<SDL_Scancode>(Key::SysReq) == SDL_SCANCODE_SYSREQ);
		static_assert(static_cast<SDL_Scancode>(Key::Cancel) == SDL_SCANCODE_CANCEL);
		static_assert(static_cast<SDL_Scancode>(Key::Clear) == SDL_SCANCODE_CLEAR);
		static_assert(static_cast<SDL_Scancode>(Key::Prior) == SDL_SCANCODE_PRIOR);
		static_assert(static_cast<SDL_Scancode>(Key::Return2) == SDL_SCANCODE_RETURN2);
		static_assert(static_cast<SDL_Scancode>(Key::Separator) == SDL_SCANCODE_SEPARATOR);
		static_assert(static_cast<SDL_Scancode>(Key::Out) == SDL_SCANCODE_OUT);
		static_assert(static_cast<SDL_Scancode>(Key::Oper) == SDL_SCANCODE_OPER);
		static_assert(static_cast<SDL_Scancode>(Key::ClearAgain) == SDL_SCANCODE_CLEARAGAIN);
		static_assert(static_cast<SDL_Scancode>(Key::CrSel) == SDL_SCANCODE_CRSEL);
		static_assert(static_cast<SDL_Scancode>(Key::ExSel) == SDL_SCANCODE_EXSEL);
		static_assert(static_cast<SDL_Scancode>(Key::Kp00) == SDL_SCANCODE_KP_00);
		static_assert(static_cast<SDL_Scancode>(Key::Kp000) == SDL_SCANCODE_KP_000);
		static_assert(static_cast<SDL_Scancode>(Key::ThousandsSeparator) == SDL_SCANCODE_THOUSANDSSEPARATOR);
		static_assert(static_cast<SDL_Scancode>(Key::DecimalSeparator) == SDL_SCANCODE_DECIMALSEPARATOR);
		static_assert(static_cast<SDL_Scancode>(Key::CurrencyUnit) == SDL_SCANCODE_CURRENCYUNIT);
		static_assert(static_cast<SDL_Scancode>(Key::CurrencySubunit) == SDL_SCANCODE_CURRENCYSUBUNIT);
		static_assert(static_cast<SDL_Scancode>(Key::KpLeftParen) == SDL_SCANCODE_KP_LEFTPAREN);
		static_assert(static_cast<SDL_Scancode>(Key::KpRightParen) == SDL_SCANCODE_KP_RIGHTPAREN);
		static_assert(static_cast<SDL_Scancode>(Key::KpLeftBrace) == SDL_SCANCODE_KP_LEFTBRACE);
		static_assert(static_cast<SDL_Scancode>(Key::KpRightBrace) == SDL_SCANCODE_KP_RIGHTBRACE);
		static_assert(static_cast<SDL_Scancode>(Key::KpTab) == SDL_SCANCODE_KP_TAB);
		static_assert(static_cast<SDL_Scancode>(Key::KpBackspace) == SDL_SCANCODE_KP_BACKSPACE);
		static_assert(static_cast<SDL_Scancode>(Key::KpA) == SDL_SCANCODE_KP_A);
		static_assert(static_cast<SDL_Scancode>(Key::KpB) == SDL_SCANCODE_KP_B);
		static_assert(static_cast<SDL_Scancode>(Key::KpC) == SDL_SCANCODE_KP_C);
		static_assert(static_cast<SDL_Scancode>(Key::KpD) == SDL_SCANCODE_KP_D);
		static_assert(static_cast<SDL_Scancode>(Key::KpE) == SDL_SCANCODE_KP_E);
		static_assert(static_cast<SDL_Scancode>(Key::KpF) == SDL_SCANCODE_KP_F);
		static_assert(static_cast<SDL_Scancode>(Key::KpXOR) == SDL_SCANCODE_KP_XOR);
		static_assert(static_cast<SDL_Scancode>(Key::KpPower) == SDL_SCANCODE_KP_POWER);
		static_assert(static_cast<SDL_Scancode>(Key::KpPercent) == SDL_SCANCODE_KP_PERCENT);
		static_assert(static_cast<SDL_Scancode>(Key::KpLess) == SDL_SCANCODE_KP_LESS);
		static_assert(static_cast<SDL_Scancode>(Key::KpGreater) == SDL_SCANCODE_KP_GREATER);
		static_assert(static_cast<SDL_Scancode>(Key::KpAmpersand) == SDL_SCANCODE_KP_AMPERSAND);
		static_assert(static_cast<SDL_Scancode>(Key::KpDblAmpersand) == SDL_SCANCODE_KP_DBLAMPERSAND);
		static_assert(static_cast<SDL_Scancode>(Key::KpVerticalBar) == SDL_SCANCODE_KP_VERTICALBAR);
		static_assert(static_cast<SDL_Scancode>(Key::KpDblVerticalBar) == SDL_SCANCODE_KP_DBLVERTICALBAR);
		static_assert(static_cast<SDL_Scancode>(Key::KpColon) == SDL_SCANCODE_KP_COLON);
		static_assert(static_cast<SDL_Scancode>(Key::KpHash) == SDL_SCANCODE_KP_HASH);
		static_assert(static_cast<SDL_Scancode>(Key::KpSpace) == SDL_SCANCODE_KP_SPACE);
		static_assert(static_cast<SDL_Scancode>(Key::KpAt) == SDL_SCANCODE_KP_AT);
		static_assert(static_cast<SDL_Scancode>(Key::KpExclamationMark) == SDL_SCANCODE_KP_EXCLAM);
		static_assert(static_cast<SDL_Scancode>(Key::KpMemStore) == SDL_SCANCODE_KP_MEMSTORE);
		static_assert(static_cast<SDL_Scancode>(Key::KpMemRecall) == SDL_SCANCODE_KP_MEMRECALL);
		static_assert(static_cast<SDL_Scancode>(Key::KpMemClear) == SDL_SCANCODE_KP_MEMCLEAR);
		static_assert(static_cast<SDL_Scancode>(Key::KpMemAdd) == SDL_SCANCODE_KP_MEMADD);
		static_assert(static_cast<SDL_Scancode>(Key::KpMemSubtract) == SDL_SCANCODE_KP_MEMSUBTRACT);
		static_assert(static_cast<SDL_Scancode>(Key::KpMemMultiply) == SDL_SCANCODE_KP_MEMMULTIPLY);
		static_assert(static_cast<SDL_Scancode>(Key::KpMemDivide) == SDL_SCANCODE_KP_MEMDIVIDE);
		static_assert(static_cast<SDL_Scancode>(Key::KpPlusMinus) == SDL_SCANCODE_KP_PLUSMINUS);
		static_assert(static_cast<SDL_Scancode>(Key::KpClear) == SDL_SCANCODE_KP_CLEAR);
		static_assert(static_cast<SDL_Scancode>(Key::KpClearEntry) == SDL_SCANCODE_KP_CLEARENTRY);
		static_assert(static_cast<SDL_Scancode>(Key::KpBinary) == SDL_SCANCODE_KP_BINARY);
		static_assert(static_cast<SDL_Scancode>(Key::KpOctal) == SDL_SCANCODE_KP_OCTAL);
		static_assert(static_cast<SDL_Scancode>(Key::KpDecimal) == SDL_SCANCODE_KP_DECIMAL);
		static_assert(static_cast<SDL_Scancode>(Key::KpHex) == SDL_SCANCODE_KP_HEXADECIMAL);
		static_assert(static_cast<SDL_Scancode>(Key::LeftCtrl) == SDL_SCANCODE_LCTRL);
		static_assert(static_cast<SDL_Scancode>(Key::LeftShift) == SDL_SCANCODE_LSHIFT);
		static_assert(static_cast<SDL_Scancode>(Key::LeftAlt) == SDL_SCANCODE_LALT);
		static_assert(static_cast<SDL_Scancode>(Key::LeftGui) == SDL_SCANCODE_LGUI);
		static_assert(static_cast<SDL_Scancode>(Key::RightCtrl) == SDL_SCANCODE_RCTRL);
		static_assert(static_cast<SDL_Scancode>(Key::RightShift) == SDL_SCANCODE_RSHIFT);
		static_assert(static_cast<SDL_Scancode>(Key::RightAlt) == SDL_SCANCODE_RALT);
		static_assert(static_cast<SDL_Scancode>(Key::RightGui) == SDL_SCANCODE_RGUI);
		static_assert(static_cast<SDL_Scancode>(Key::Count) == SDL_NUM_SCANCODES);

		self->OnEvent(KeyboardEventArgs{
			.Key = static_cast<Key>(event.keysym.scancode),
			.Pressed = event.state == SDL_PRESSED,
		});
	}

	auto Window::HandleEvent(const SDL_MouseButtonEvent& event) -> void
	{
		auto* self = GetCurrentWindow(event.windowID);

		static constexpr std::array sdlButtonMappings{
			Button{-1},
			Button::M1,
			Button::M3,
			Button::M2,
			Button::M4,
			Button::M5,
		};

		static_assert(sdlButtonMappings[SDL_BUTTON_LEFT] == Button::M1);
		static_assert(sdlButtonMappings[SDL_BUTTON_RIGHT] == Button::M2);
		static_assert(sdlButtonMappings[SDL_BUTTON_MIDDLE] == Button::M3);
		static_assert(sdlButtonMappings[SDL_BUTTON_X1] == Button::M4);
		static_assert(sdlButtonMappings[SDL_BUTTON_X2] == Button::M5);

		self->OnEvent(MouseButtonEventArgs{
			.Button = sdlButtonMappings.at(event.button),
			.Pressed = event.state == SDL_PRESSED,
			.Position = glm::i32vec2({
				event.x,
				event.y,
			}),
		});
	}

	auto Window::HandleEvent(const SDL_MouseMotionEvent& event) -> void
	{
		auto* self = GetCurrentWindow(event.windowID);

		self->OnEvent(MouseMotionEventArgs{
			.Position = glm::i32vec2({
				event.x,
				event.y,
			}),
			.Movement = glm::i32vec2({
				event.xrel,
				event.yrel,
			}),
		});
	}

	auto Window::HandleEvent(const SDL_MouseWheelEvent& event) -> void
	{
		auto* self = GetCurrentWindow(event.windowID);

		self->OnEvent(MouseScrollEventArgs{
			.Scroll = glm::vec2({
				event.preciseX,
				event.preciseY,
			}),
		});
	}

	auto Window::HandleEvent(const SDL_TextInputEvent& event) -> void
	{
		auto* self = GetCurrentWindow(event.windowID);

		self->OnEvent(TextInputEventArgs{
			.Text = static_cast<const char*>(event.text),
		});
	}

	auto Window::Handle() const -> SDL_Window*
	{
		return m_Window.get();
	}

	auto Window::WindowListener() const -> IWindowListener*
	{
		return m_WindowListener;
	}

	auto Window::WindowListener(IWindowListener* listener) -> void
	{
		m_WindowListener = listener;
	}

	auto Window::InputListener() const -> IInputListener*
	{
		return m_InputListener;
	}

	auto Window::InputListener(IInputListener* listener) -> void
	{
		m_InputListener = listener;
	}

	auto Window::TextListener() const -> ITextListener*
	{
		return m_TextListener;
	}

	auto Window::TextListener(ITextListener* listener) -> void
	{
		m_TextListener = listener;
	}

	auto Window::OnEvent(const WindowCloseEventArgs& event) -> void
	{
		if (m_WindowListener != nullptr)
			m_WindowListener->OnEvent(this, event);
	}

	auto Window::OnEvent(const WindowResizeEventArgs& event) -> void
	{
		if (m_WindowListener != nullptr)
			m_WindowListener->OnEvent(this, event);
	}

	auto Window::OnEvent(const MouseFocusChancedEventArgs& event) -> void
	{
		if (m_WindowListener != nullptr)
			m_WindowListener->OnEvent(this, event);
	}

	auto Window::OnEvent(const KeyboardFocusChancedEventArgs& event) -> void
	{
		if (m_WindowListener != nullptr)
			m_WindowListener->OnEvent(this, event);
	}

	auto Window::OnEvent(const KeyboardEventArgs& event) -> void
	{
		if (m_InputListener != nullptr)
			m_InputListener->OnEvent(this, event);
	}

	auto Window::OnEvent(const MouseButtonEventArgs& event) -> void
	{
		if (m_InputListener != nullptr)
			m_InputListener->OnEvent(this, event);
	}

	auto Window::OnEvent(const MouseMotionEventArgs& event) -> void
	{
		if (m_InputListener != nullptr)
			m_InputListener->OnEvent(this, event);
	}

	auto Window::OnEvent(const MouseScrollEventArgs& event) -> void
	{
		if (m_InputListener != nullptr)
			m_InputListener->OnEvent(this, event);
	}

	auto Window::OnEvent(const TextInputEventArgs& event) -> void
	{
		if (m_TextListener != nullptr)
			m_TextListener->OnEvent(this, event);
	}
} //namespace Star
