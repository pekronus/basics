#ifndef __ActivationFunc_H__
#define _ActivationFunc_H__

#include <string>
#include <math.h>

namespace pekronus
{
    enum class ActivationFuncType
        {
            Sigmoid
        };
    template <class T>
    class ActivationFunc
    {
      public:
        
        //! calculate the function value
        virtual T f(const T x) const = 0;
        //! derivative.  also calculates the function value
        virtual T dfdx(const T x, T& fval) const = 0;
        //! create a functor object based on type
        static ActivationFunc<T>* create(const ActivationFuncType ft);
        //! clone
        virtual ActivationFunc<T>* clone() const = 0;
    };

    template <class T>
    class SigmoidAF : public ActivationFunc<T>
    {
      public:
        //! compute value
        T f(const T x) const
          {return 1.0/(1+std::exp(-x));}
        //! compute derivative
        T dfdx(const T x, T& fval) const
          {
              fval = f(x);
              return fval*(1-fval);
          }
       
        //! clone
        virtual ActivationFunc<T>* clone() const
          {
              return new SigmoidAF();
          }
    };

    template<class T>
    ActivationFunc<T>*
    ActivationFunc<T>::create(const ActivationFuncType ft)
    {
        switch (ft)
        {
          case ActivationFuncType::Sigmoid:
            return new SigmoidAF<T>();
          default:
            return nullptr;
        }
    }
}

#endif
