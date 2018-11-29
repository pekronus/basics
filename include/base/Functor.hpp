#ifndef __Functor_H__
#define __Functor_H__

namespace pekronus
{
    //! 1 variable functor interface
    template <class T>
    class Functor1D
    {
      public:
        //! evaluate at x
        virtual T operator(const T& x) const = 0;
    };

    //! 2 variable functor interface
    template <class T>
    class Functor2D
    {
      public:
        virtual T operator(const T& x, const T& y) const = 0;
    }
}
#endif
