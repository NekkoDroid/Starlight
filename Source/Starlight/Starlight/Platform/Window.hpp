#pragma once

#include <glm/vec2.hpp>

#include <memory>
#include <stdexcept>
#include <string_view>

struct SDL_Window;
struct SDL_WindowEvent;
struct SDL_KeyboardEvent;
struct SDL_MouseButtonEvent;
struct SDL_MouseMotionEvent;
struct SDL_MouseWheelEvent;
struct SDL_TextInputEvent;

namespace Star
{
	/// @brief Keyboard scancodes based on the USB standard.
	/// @see https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf
	enum class Key
	{
		/// @brief Key for any unknown scancodes.
		Unknown = 0,

		/// @brief Letter "A".
		A = 4,

		/// @brief Letter "B".
		B = 5,

		/// @brief Letter "C".
		C = 6,

		/// @brief Letter "D".
		D = 7,

		/// @brief Letter "E".
		E = 8,

		/// @brief Letter "F".
		F = 9,

		/// @brief Letter "G".
		G = 10,

		/// @brief Letter "H".
		H = 11,

		/// @brief Letter "I".
		I = 12,

		/// @brief Letter "J".
		J = 13,

		/// @brief Letter "K".
		K = 14,

		/// @brief Letter "L".
		L = 15,

		/// @brief Letter "M".
		M = 16,

		/// @brief Letter "N".
		N = 17,

		/// @brief Letter "O".
		O = 18,

		/// @brief Letter "P".
		P = 19,

		/// @brief Letter "Q".
		Q = 20,

		/// @brief Letter "R".
		R = 21,

		/// @brief Letter "S".
		S = 22,

		/// @brief Letter "T".
		T = 23,

		/// @brief Letter "U".
		U = 24,

		/// @brief Letter "V".
		V = 25,

		/// @brief Letter "W".
		W = 26,

		/// @brief Letter "X".
		X = 27,

		/// @brief Letter "Y".
		Y = 28,

		/// @brief Letter "Z".
		Z = 29,

		/// @brief Number "1".
		Nr1 = 30,

		/// @brief Number "2".
		Nr2 = 31,

		/// @brief Number "3".
		Nr3 = 32,

		/// @brief Number "4".
		Nr4 = 33,

		/// @brief Number "5".
		Nr5 = 34,

		/// @brief Number "6".
		Nr6 = 35,

		/// @brief Number "7".
		Nr7 = 36,

		/// @brief Number "8".
		Nr8 = 37,

		/// @brief Number "9".
		Nr9 = 38,

		/// @brief Number "0".
		Nr0 = 39,

		/// @brief Return/enter.
		Return = 40,

		/// @brief Escape.
		Escape = 41,

		/// @brief Delete/backspace.
		Backspace = 42,

		/// @brief Tab.
		Tab = 43,

		/// @brief Spacebar.
		Space = 44,

		/// @brief Character "-".
		Minus = 45,

		/// @brief Character "=".
		Equals = 46,

		/// @brief Character "[".
		LeftBracket = 47,

		/// @brief Character "]".
		RightBracket = 48,

		/// @brief Character "\\".
		Backslash = 49,

		/// @brief Character "#" (Non-US)
		NonUSHash = 50,

		/// @brief Character ";".
		Semicolon = 51,

		/// @brief Character "'".
		Apostrophe = 52,

		/// @brief Character "`".
		Grave = 53,

		/// @brief Character ",".
		Comma = 54,

		/// @brief Character ".".
		Period = 55,

		/// @brief Character "/".
		Slash = 56,

		/// @brief Caps lock.
		CapsLock = 57,

		/// @brief Function key 1.
		F1 = 58,

		/// @brief Function key 2.
		F2 = 59,

		/// @brief Function key 3.
		F3 = 60,

		/// @brief Function key 4.
		F4 = 61,

		/// @brief Function key 5.
		F5 = 62,

		/// @brief Function key 6.
		F6 = 63,

		/// @brief Function key 7.
		F7 = 64,

		/// @brief Function key 8.
		F8 = 65,

		/// @brief Function key 9.
		F9 = 66,

		/// @brief Function key 10.
		F10 = 67,

		/// @brief Function key 11.
		F11 = 68,

		/// @brief Function key 12.
		F12 = 69,

		/// @brief Print screen.
		PrintScreen = 70,

		/// @brief Scroll lock.
		ScrollLock = 71,

		/// @brief Pause.
		Pause = 72,

		/// @brief Insert.
		Insert = 73,

		/// @brief Home.
		Home = 74,

		/// @brief Page up.
		PageUp = 75,

		/// @brief Delete.
		Delete = 76,

		/// @brief End.
		End = 77,

		/// @brief Page down.
		PageDown = 78,

		/// @brief Right arrow key.
		Right = 79,

		/// @brief Left arrow key.
		Left = 80,

		/// @brief Down arrow key.
		Down = 81,

		/// @brief Up arrow key.
		Up = 82,

		/// @brief Number lock.
		NumLock = 83,

		/// @brief Keypad divide.
		KpDivide = 84,

		/// @brief Keypad multiply.
		KpMultiply = 85,

		/// @brief Keypad minus.
		KpMinus = 86,

		/// @brief Keypad plus.
		KpPlus = 87,

		/// @brief Keypad enter.
		KpEnter = 88,

		/// @brief Keypad number "1".
		Kp1 = 89,

		/// @brief Keypad number "2".
		Kp2 = 90,

		/// @brief Keypad number "3".
		Kp3 = 91,

		/// @brief Keypad number "4".
		Kp4 = 92,

		/// @brief Keypad number "5".
		Kp5 = 93,

		/// @brief Keypad number "6".
		Kp6 = 94,

		/// @brief Keypad number "7".
		Kp7 = 95,

		/// @brief Keypad number "8".
		Kp8 = 96,

		/// @brief Keypad number "9".
		Kp9 = 97,

		/// @brief Keypad number "0".
		Kp0 = 98,

		/// @brief Keypad character ".".
		KpPeriod = 99,

		/// @brief Non-US character "\\".
		NonUSBackslash = 100,

		/// @brief Application.
		Application = 101,

		/// @brief Power.
		Power = 102,

		/// @brief Keypad character "=".
		KpEquals = 103,

		/// @brief Function key 13.
		F13 = 104,

		/// @brief Function key 14.
		F14 = 105,

		/// @brief Function key 15.
		F15 = 106,

		/// @brief Function key 16.
		F16 = 107,

		/// @brief Function key 17.
		F17 = 108,

		/// @brief Function key 18.
		F18 = 109,

		/// @brief Function key 19.
		F19 = 110,

		/// @brief Function key 20.
		F20 = 111,

		/// @brief Function key 21.
		F21 = 112,

		/// @brief Function key 22.
		F22 = 113,

		/// @brief Function key 23.
		F23 = 114,

		/// @brief Function key 24.
		F24 = 115,

		/// @brief Execute.
		Execute = 116,

		/// @brief Help.
		Help = 117,

		/// @brief Menu.
		Menu = 118,

		/// @brief Select.
		Select = 119,

		/// @brief Stop.
		Stop = 120,

		/// @brief Redo/again.
		Redo = 121,

		/// @brief Undo.
		Undo = 122,

		/// @brief Cut.
		Cut = 123,

		/// @brief Copy.
		Copy = 124,

		/// @brief Paste.
		Paste = 125,

		/// @brief Find.
		Find = 126,

		/// @brief Mute.
		Mute = 127,

		/// @brief Volume up.
		VolumeUp = 128,

		/// @brief Volume down.
		VolumeDown = 129,

		/// @brief Keypad character ",".
		KpComma = 133,

		/// @brief Keypad equals as 400.
		KpEqualsAs400 = 134,

		/// @brief International 1.
		International1 = 135,

		/// @brief International 2.
		International2 = 136,

		/// @brief International 3.
		International3 = 137,

		/// @brief International 4.
		International4 = 138,

		/// @brief International 5.
		International5 = 139,

		/// @brief International 6.
		International6 = 140,

		/// @brief International 7.
		International7 = 141,

		/// @brief International 8.
		International8 = 142,

		/// @brief International 9.
		International9 = 143,

		/// @brief Language 1.
		Lang1 = 144,

		/// @brief Language 2.
		Lang2 = 145,

		/// @brief Language 3.
		Lang3 = 146,

		/// @brief Language 4.
		Lang4 = 147,

		/// @brief Language 5.
		Lang5 = 148,

		/// @brief Language 6.
		Lang6 = 149,

		/// @brief Language 7.
		Lang7 = 150,

		/// @brief Language 8.
		Lang8 = 151,

		/// @brief Language 9.
		Lang9 = 152,

		/// @brief Alternate erase.
		AltErase = 153,

		/// @brief System request.
		SysReq = 154,

		/// @brief Cancel.
		Cancel = 155,

		/// @brief Clear.
		Clear = 156,

		/// @brief Prior.
		Prior = 157,

		/// @brief Secondary return.
		Return2 = 158,

		/// @brief Separator.
		Separator = 159,

		/// @brief Out.
		Out = 160,

		/// @brief Oper.
		Oper = 161,

		/// @brief Clear/again.
		ClearAgain = 162,

		/// @brief CrSel.
		CrSel = 163,

		/// @brief ExSel.
		ExSel = 164,

		/// @brief Keypad number "00".
		Kp00 = 176,

		/// @brief Keypad number "000".
		Kp000 = 177,

		/// @brief Locale dependent thousands separator character.
		ThousandsSeparator = 178,

		/// @brief Locale dependent decimal separator character.
		DecimalSeparator = 179,

		/// @brief Locale dependent currency unit.
		CurrencyUnit = 180,

		/// @brief Locale dependent currency subunit.
		CurrencySubunit = 181,

		/// @brief Keypad character "(".
		KpLeftParen = 182,

		/// @brief Keypad character ")".
		KpRightParen = 183,

		/// @brief Keypad character "{".
		KpLeftBrace = 184,

		/// @brief Keypad character "}".
		KpRightBrace = 185,

		/// @brief Keypad tab.
		KpTab = 186,

		/// @brief Keypad backspace.
		KpBackspace = 187,

		/// @brief Keypad character "A".
		KpA = 188,

		/// @brief Keypad character "B".
		KpB = 189,

		/// @brief Keypad character "C".
		KpC = 190,

		/// @brief Keypad character "D".
		KpD = 191,

		/// @brief Keypad character "E".
		KpE = 192,

		/// @brief Keypad character "F".
		KpF = 193,

		/// @brief Keypad XOR.
		KpXOR = 194,

		/// @brief Keypad character "^".
		KpPower = 195,

		/// @brief Keypad character "%".
		KpPercent = 196,

		/// @brief Keypad character "<".
		KpLess = 197,

		/// @brief Keypad character ">".
		KpGreater = 198,

		/// @brief Keypad character "&".
		KpAmpersand = 199,

		/// @brief Keypad character "&&".
		KpDblAmpersand = 200,

		/// @brief Keypad character "|".
		KpVerticalBar = 201,

		/// @brief Keypad character "||".
		KpDblVerticalBar = 202,

		/// @brief Keypad character ":".
		KpColon = 203,

		/// @brief Keypad character "#".
		KpHash = 204,

		/// @brief Keypad space.
		KpSpace = 205,

		/// @brief Keypad character "@@".
		KpAt = 206,

		/// @brief Keypad character "!".
		KpExclamationMark = 207,

		/// @brief Keypad memory store.
		KpMemStore = 208,

		/// @brief Keypad memory recall.
		KpMemRecall = 209,

		/// @brief Keypad memory clear.
		KpMemClear = 210,

		/// @brief Keypad memory add.
		KpMemAdd = 211,

		/// @brief Keypad memory subtract.
		KpMemSubtract = 212,

		/// @brief Keypad memory multiply.
		KpMemMultiply = 213,

		/// @brief Keypad memory divide.
		KpMemDivide = 214,

		/// @brief Keypad +/-.
		KpPlusMinus = 215,

		/// @brief Keypad clear.
		KpClear = 216,

		/// @brief Keypad clear entry.
		KpClearEntry = 217,

		/// @brief Keypad binary.
		KpBinary = 218,

		/// @brief Keypad octal.
		KpOctal = 219,

		/// @brief Keypad decimal.
		KpDecimal = 220,

		/// @brief Keypad hexadecimal.
		KpHex = 221,

		/// @brief Left ctrl.
		LeftCtrl = 224,

		/// @brief Left shift.
		LeftShift = 225,

		/// @brief Left alt.
		LeftAlt = 226,

		/// @brief Left GUI.
		LeftGui = 227,

		/// @brief Right ctrl.
		RightCtrl = 228,

		/// @brief Right shift.
		RightShift = 229,

		/// @brief Right alt.
		RightAlt = 230,

		/// @brief Right GUI.
		RightGui = 231,

		/// @brief Number of keyboard scancodes.
		Count = 512,
	};

	/// @brief Mouse buttons.
	enum class Button
	{
		/// @brief Mouse button 1, also referred to as left mouse button.
		M1,

		/// @brief Mouse button 2, also referred to as right mouse button.
		M2,

		/// @brief Mouse button 3, also referred to as middle mouse button.
		M3,

		/// @brief Mouse button 4, also referred to as the backwards thumb button.
		M4,

		/// @brief Mouse button 5, also referred to as the forward thumb button.
		M5,

		/// @brief Number of mouse buttons.
		Count,
	};

	/// @brief Event information when a window is resized.
	struct WindowResizeEventArgs
	{
		/// @brief Dimensions in screen coordinates.
		glm::ivec2 Size{};

		/// @brief Dimensions in pixel count.
		glm::ivec2 Pixel{};
	};

	/// @brief Event information when mouse focus is changed.
	struct MouseFocusChancedEventArgs
	{
		/// @brief Mouse focus state.
		bool Focused{};
	};

	/// @brief Event information when keyboard focus is changed.
	struct KeyboardFocusChancedEventArgs
	{
		/// @brief Keyboard focus state.
		bool Focused{};
	};

	/// @brief Event information when a window wants to close.
	struct WindowCloseEventArgs
	{
	};

	/// @brief Event information when the keyboard state is updated.
	struct KeyboardEventArgs
	{
		/// @brief Key that has been updated.
		Key Key{};

		/// @brief Key pressed state.
		bool Pressed{};
	};

	/// @brief Event information when a mouse button has updated.
	struct MouseButtonEventArgs
	{
		/// @brief Button that has been updated.
		Button Button{};

		/// @brief Button pressed state.
		bool Pressed{};

		/// @brief Position of the click relative to the window.
		glm::i32vec2 Position{};
	};

	/// @brief Event information when the mouse is moved.
	struct MouseMotionEventArgs
	{
		/// @brief New position of the mouse relative to the window.
		glm::i32vec2 Position{};

		/// @brief Delta by how much the mouse has been moved.
		glm::i32vec2 Movement{};
	};

	/// @brief Event information when the mouse wheel is moved.
	struct MouseScrollEventArgs
	{
		/// @brief Delta by how much the mouse wheel has been moved.
		glm::vec2 Scroll{};
	};

	/// @brief Event information when text is input.
	struct TextInputEventArgs
	{
		/// @brief Text input encoded as UTF-8.
		std::string_view Text{};
	};

	class Window;

	/// @brief Window event listener.
	class IWindowListener
	{
	public:
		/// @brief Destructor.
		virtual ~IWindowListener() = default;

		/// @brief Event handler for window closing.
		/// @param sender Event sender.
		/// @param event Event arguments.
		virtual auto OnEvent(Window* sender, const WindowCloseEventArgs& event) -> void = 0;

		/// @brief Event handler for window resizing.
		/// @param sender Event sender.
		/// @param event Event arguments.
		virtual auto OnEvent(Window* sender, const WindowResizeEventArgs& event) -> void = 0;

		/// @brief Event handler for mouse focus changing.
		/// @param sender Event sender.
		/// @param event Event arguments.
		virtual auto OnEvent(Window* sender, const MouseFocusChancedEventArgs& event) -> void = 0;

		/// @brief Event handler for keyboard focus changing.
		/// @param sender Event sender.
		/// @param event Event arguments.
		virtual auto OnEvent(Window* sender, const KeyboardFocusChancedEventArgs& event) -> void = 0;
	};

	/// @brief Input event listener.
	class IInputListener
	{
	public:
		/// @brief Destructor.
		virtual ~IInputListener() = default;

		/// @brief Event handler for key updates.
		/// @param sender Event sender.
		/// @param event Event arguments.
		virtual auto OnEvent(Window* sender, const KeyboardEventArgs& event) -> void = 0;

		/// @brief Event handler for mouse button updates.
		/// @param sender Event sender.
		/// @param event Event arguments.
		virtual auto OnEvent(Window* sender, const MouseButtonEventArgs& event) -> void = 0;

		/// @brief Event handler for mouse movement.
		/// @param sender Event sender.
		/// @param event Event arguments.
		virtual auto OnEvent(Window* sender, const MouseMotionEventArgs& event) -> void = 0;

		/// @brief Event handler for mouse scrolling.
		/// @param sender Event sender.
		/// @param event Event arguments.
		virtual auto OnEvent(Window* sender, const MouseScrollEventArgs& event) -> void = 0;
	};

	/// @brief Text event listener.
	class ITextListener
	{
	public:
		/// @brief Destructor.
		virtual ~ITextListener() = default;

		/// @brief Event handler for text input.
		/// @param sender Event sender.
		/// @param event Event arguments.
		virtual auto OnEvent(Window* sender, const TextInputEventArgs& event) -> void = 0;
	};

	/// @brief Deleter used for SDL specific resources.
	struct SDLDeleter
	{
		/// @brief Destroys a specific SDL window.
		/// @param ptr Window to destroy.
		auto operator()(SDL_Window* ptr) const noexcept -> void;
	};

	/// @brief Unique pointer for SDL specific resources.
	template <typename TType>
	using SDLPointer = std::unique_ptr<TType, SDLDeleter>;

	/// @brief Exception raised when a window specific error happens.
	struct WindowException : std::runtime_error
	{
		using runtime_error::runtime_error;
	};

	/// @brief Class representing a platform window.
	class Window
	{
	public:
		/// @brief Create a new window instance.
		/// @param title Title displayed in the title bar.
		/// @param size Width and height of the window.
		/// @param flags Flags passed to the underlying SDL window.
		explicit Window(const char* title, glm::ivec2 size, uint32_t flags);

		/// @brief Destructor.
		virtual ~Window() = default;

		/// @brief Copy constructor.
		/// @param other Window to copy from.
		Window(const Window& other) = delete;

		/// @brief Move constructor.
		/// @param other Window to move from.
		Window(Window&& other) noexcept;

		/// @brief Copy operator.
		/// @param other Window to copy from.
		/// @return Reference to the current window.
		auto operator=(const Window& other) -> Window& = delete;

		/// @brief Move operator.
		/// @param other Window to move from.
		/// @return Reference to the current window.
		auto operator=(Window&& other) noexcept -> Window&;

		/// @brief Dispatches an event to the appropriate window.
		/// @param event Event to dispatch.
		static auto HandleEvent(const SDL_WindowEvent& event) -> void;

		/// @brief Dispatches an event to the appropriate window.
		/// @param event Event to dispatch.
		static auto HandleEvent(const SDL_KeyboardEvent& event) -> void;

		/// @brief Dispatches an event to the appropriate window.
		/// @param event Event to dispatch.
		static auto HandleEvent(const SDL_MouseButtonEvent& event) -> void;

		/// @brief Dispatches an event to the appropriate window.
		/// @param event Event to dispatch.
		static auto HandleEvent(const SDL_MouseMotionEvent& event) -> void;

		/// @brief Dispatches an event to the appropriate window.
		/// @param event Event to dispatch.
		static auto HandleEvent(const SDL_MouseWheelEvent& event) -> void;

		/// @brief Dispatches an event to the appropriate window.
		/// @param event Event to dispatch.
		static auto HandleEvent(const SDL_TextInputEvent& event) -> void;

		/// @brief Get the underlying handle of this window.
		/// @return Underlying handle.
		[[nodiscard]] auto Handle() const -> SDL_Window*;

		/// @brief Get the window event listener of this window.
		/// @return Current window event listener.
		[[nodiscard]] auto WindowListener() const -> IWindowListener*;

		/// @brief Set the window event listener for this window.
		/// @param listener New window event listener.
		auto WindowListener(IWindowListener* listener) -> void;

		/// @brief Get the input event listener of this window.
		/// @return Current input event listener.
		[[nodiscard]] auto InputListener() const -> IInputListener*;

		/// @brief Set the input event listener for this window.
		/// @param listener New input event listener.
		auto InputListener(IInputListener* listener) -> void;

		/// @brief Get the text event listener of this window.
		/// @return Current text event listener.
		[[nodiscard]] auto TextListener() const -> ITextListener*;

		/// @brief Set the text event listener for this window.
		/// @param listener New text event listener.
		auto TextListener(ITextListener* listener) -> void;

	protected:
		/// @brief Event handler for window closing.
		/// @param event Event arguments.
		virtual auto OnEvent(const WindowCloseEventArgs& event) -> void;

		/// @brief Event handler for window resizing.
		/// @param event Event arguments.
		virtual auto OnEvent(const WindowResizeEventArgs& event) -> void;

		/// @brief Event handler for mouse focus changing.
		/// @param event Event arguments.
		virtual auto OnEvent(const MouseFocusChancedEventArgs& event) -> void;

		/// @brief Event handler for keyboard focus changing.
		/// @param event Event arguments.
		virtual auto OnEvent(const KeyboardFocusChancedEventArgs& event) -> void;

		/// @brief Event handler for key updates.
		/// @param event Event arguments.
		virtual auto OnEvent(const KeyboardEventArgs& event) -> void;

		/// @brief Event handler for mouse button updates.
		/// @param event Event arguments.
		virtual auto OnEvent(const MouseButtonEventArgs& event) -> void;

		/// @brief Event handler for mouse movement.
		/// @param event Event arguments.
		virtual auto OnEvent(const MouseMotionEventArgs& event) -> void;

		/// @brief Event handler for mouse scrolling.
		/// @param event Event arguments.
		virtual auto OnEvent(const MouseScrollEventArgs& event) -> void;

		/// @brief Event handler for text input.
		/// @param event Event arguments.
		virtual auto OnEvent(const TextInputEventArgs& event) -> void;

	private:
		SDLPointer<SDL_Window> m_Window{};

		IWindowListener* m_WindowListener{};
		IInputListener* m_InputListener{};
		ITextListener* m_TextListener{};
	};
} //namespace Star
