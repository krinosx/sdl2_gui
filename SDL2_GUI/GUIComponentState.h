/**
 * \enum GUIComponentState
 * @brief List component states. Used to handle transitions and event.
 */
enum GUIComponentState { 
    base, /**< initial state for all components */
    pressed, /**< State when a click event is pressed on top of this component */
    released, /**< State when a click event is released on top of this component */
    editing  /**< State when the content of the component is being edited. e.g. Text editors components */
};