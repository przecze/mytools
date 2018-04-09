#pragma once

namespace mytools {
template<class T>
T&& move(T&t) { return static_cast<T&&>(t);}

template <class Lambda, class Lambda2>
class Button
{
  public:
    Button(Lambda&& check, Lambda2&& action):
      is_pressed(move(check)),
      handle(move(action))
    {}

    int count = 0;
    int down_count = 0;
    bool ready = false;
    Lambda is_pressed;
    Lambda2 handle;
    void CheckAndHandle()
    {
        if(is_pressed())
        {
            count++;
            down_count = 0;
        }
        else
        {
            down_count++;
            count = 0;
        }

        if(count == 3 && ready)
        {
            handle();
            ready = false;
        }
        if(down_count == 3)
        {
            ready = true;
        }
    }
};

template <class Lambda, class Lambda2>
Button<Lambda, Lambda2> make_button(Lambda&& a, Lambda2&& b)
{
    return Button<Lambda, Lambda2>(move(a),move(b));
}

}
