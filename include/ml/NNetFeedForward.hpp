#ifndef __NNetFeedForward_H__
#define __NNetFeedForward_H__

#include <vector>
#include <ml/ActivationFunc.hpp>


namespace pekronus
{
    template <class DType>
    class NNetFeedForward
    {
      public:
        //! represents a single layer
        class Layer
        {
            ActivationFunc<DType>& _afunc;
            int nnodes;
        };
        //! default ctor
        NNetFeedForward();
        //! add a layer
        
        
      protected:

        //! layers
        std::vector<Layer> _layers;
        //! weights (layer/ node to / node from) 
        std::vector< std::vector< std::vector<DType> > > _weights;
    };
};


#endif
