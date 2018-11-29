#include <ml/ActivationFunc.hpp>

using namespace pekronus;

template<class T>
ActivationFunc<T>*
ActivationFunc<T>::create(const ActivationFunc::FuncType ft)
{
    switch (ft)
    {
      case FuncType::SigmoidAF:
        return new SigmoidAF<T>();
    }
}
