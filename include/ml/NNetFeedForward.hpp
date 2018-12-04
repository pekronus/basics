#ifndef __NNetFeedForward_H__
#define __NNetFeedForward_H__

#include <vector>
#include <memory>
#include <ml/ActivationFunc.hpp>



namespace pekronus
{
    template <class DType>
    class NNetFeedForwardGeometry
    {
      public:
        //! default ctor
        NNetFeedForwardGeometry();
        
        // represents a network node
        struct Node
        {
            Node()
                : _in_val(0.), _out_val(0.0), _dout_din(0.0)
              {}
            DType _in_val; //! value of the input
            DType _out_val; //! value of activation function
            DType _dout_din; //! derivative of output wrt input
        };
        //! represents a single layer
        struct Layer
        {
            std::unique_ptr<ActivationFunc<DType> > _afunc;
            std::vector<Node> _nodes;
        };

        //! add a layer
        void add_layer(const int nnodes, const ActivationFunc<DType>* af);

        // get number of layers
        int number_of_layers() const
          {return _layers.size();}
        //! get number of nodes
        int number_of_nodes() const;
        //! get number of nodes for a layer
        int number_of_nodes(int layer) const
          {return _layers[layer]._nodes.size();}
        //! get reference to node ion layer l
        Node& node(const int i, const int l)
          {return _layers[l]._nodes[i];}
        //! get reference to node ion layer l constant version
        const Node& node(const int i, const int l) const
          {return _layers[l]._nodes[i];}
        
      protected:
        //! layers
        std::vector<Layer> _layers;
    };
    
    template <class DType>
    class NNetFeedForward : public NNetFeedForwardGeometry<DType>
    {
      public:
        //! default ctor
        NNetFeedForward();
        //! propagate forward
        const std::vector<typename NNetFeedForwardGeometry<DType>::Node>& propagate_forward(const std::vector<DType>& inputs);
        //! calculate derivatives wrt to weights
        void back_propagate(
            std::vector< std::vector< std::vector<DType> > >& partials) const;
        //! set weights
        void set_weights(
            const std::vector< std::vector< std::vector<DType> > >& weights);
        //! increment weights
        void incr_weights(
            const std::vector< std::vector< std::vector<DType> > >& increments);
      protected:

        
        //! weights (layer/ node-to / node-from) 
        std::vector< std::vector< std::vector<DType> > > _weights;
    };

    //! ctor
    template <class DType>
    NNetFeedForwardGeometry<DType>::NNetFeedForwardGeometry()
    {}

    //! add a layer
    template <class DType>
    void
    NNetFeedForwardGeometry<DType>::add_layer(const int nnodes,
                                              const ActivationFunc<DType>* af)
    {
        Layer l;
        l._nodes.resize(nnodes);
        l._afunc.reset(af);
        _layers.push_back(l);
    }


    template <class DType>
    NNetFeedForward<DType>::NNetFeedForward()
        : NNetFeedForwardGeometry<DType>()
    {}
};

#endif
