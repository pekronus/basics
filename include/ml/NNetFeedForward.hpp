#ifndef __NNetFeedForward.hpp_H__
#define __NNetFeedForward.hpp_H__

#include <vector>


namespace pekronus
{
    class NNetFeedForward
    {
      public:

      protected:
        //! number of layers
        int nlayers;
        std::vector<int> nodes_per_layer;
    };
};


#endif
