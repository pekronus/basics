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
        virtual T operator()(const T& x) const
          {return f(x);}
        //! evaluate at x
        virtual T f(const T& x) const = 0;
        //! evaluate derivative at x
        virtual T dfdx(const T& x) const
          {
              static const T dx = 1e-8;
              return (f(x+dx) - f(x))/dx;
          }
    };

    //! 2 variable functor interface
    template <class T>
    class Functor2D
    {
      public:
        virtual T operator()(const T& x, const T& y) const = 0;
    };
}
#endif
