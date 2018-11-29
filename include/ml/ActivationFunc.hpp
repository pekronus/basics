#ifndef __ActivationFunc_H__
#define _ActivationFunc_H__

#include <base/Functor.hpp>

#include <string>
#include <math.h>

namespace pekronus
{
    template <class T>
    class ActivationFunc : public Functor1D<T>
    {
      public:
        enum class FuncType
            {
                Sigmoid
            };
        //! derivative
        virtual T dfdx(const T& x) const = 0;
        //! create a functor object based on type
        static ActivationFunc<T>* create(const FuncType ft);
        
    };

    template <class T>
    class SigmoidAF : public ActivationFunc<T>
    {
      public:
        //! compute value
        T f(const T& x) const
          {return 1.0/(1+std::exp(-x));}
        //! compute derivative
        T dfdx(const T& x) const
          {
              T t = std::exp(-x);
              T tt = 1+std::exp(-x);
              return t/tt/tt;
          }
    };

}

#endif
