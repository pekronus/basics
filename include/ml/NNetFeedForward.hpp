#ifndef __NNetFeedForward_H__
#define __NNetFeedForward_H__

#include <base/Matrix.hpp>
#include <ml/ActivationFunc.hpp>

#include <vector>
#include <memory>
#include <exception>


namespace pekronus
{
    template <class DType>
    class NNetFeedForward
    {
      public:
        //!  ctor
        NNetFeedForward(const std::vector<unsigned int> nodes_per_layer,
                        typename ActivationFunc<DType>::FuncType aft);
        
        // represents a network node
        // struct Node
        // {
        //     Node()
        //         : _in_val(0.), _out_val(0.0), _dout_din(0.0)
        //       {}
        //     DType _in_val; //! value of the input
        //     DType _out_val; //! value of activation function
        //     DType _dout_din; //! derivative of output wrt input
        // };
        //! represents a single layer
        struct Layer
        {
            //! default ctor
            Layer()
              {}
            Layer(const int n)
              {
                  _in_vals.assign(n, 0.0);
                  _out_vals.assign(n, 0.0);
                  _dout_dins.assign(0.0);
              }
            void resize(const int n)
              {
                  _in_vals.assign(n, 0.0);
                  _out_vals.assign(n, 0.0);
                  _dout_dins.assign(0.0);
              }
            std::unique_ptr<ActivationFunc<DType> > _afunc;
            std::vector<DType> _in_vals;
            std::vector<DType> _out_vals;
            std::vector<DType> _dout_dins;
            
        };

        // get number of layers
        int number_of_layers() const
          {return _layers.size();}
        //! get number of nodes
        int number_of_nodes() const;
        //! get number of nodes for a layer
        int number_of_nodes(int layer) const
          {return _layers[layer]._out_vals.size();}
        //! get value of node i on layer l
        DType value(const int i, const int l) const
          {return _layers[l]._out_vals[i];}

        //! propagate forward
        const std::vector<DType>& propagate_forward(const std::vector<DType>& inputs);
        //! calculate derivatives wrt to weights
        void back_propagate(
            std::vector< Matrix<DType> >& partials) const;
        //! set weights
        void set_weights(
            const std::vector< Matrix<DType> >& weights);
        //! increment weights
        void incr_weights(
            const std::vector< Matrix<DType> >& increments);
      protected:
        //! layers
        std::vector<Layer> _layers;
        //! weights (layer/ node-to / node-from (last one is the bias)) 
        std::vector< Matrix<DType> > _weights;
    };

    
    //! ctor
    template <class DType>
    NNetFeedForward<DType>::NNetFeedForward(const std::vector<unsigned int> nodes_per_layer,
                                            typename ActivationFunc<DType>::FuncType aft)
    {
        auto nlayers = nodes_per_layer.size();
        if (nlayers == 0)
            return;
        // add all layers but the last one
        for (auto i = 0; i < nlayers-1; ++i)
        {
            Layer l;
            l.resize(nodes_per_layer[i]);
            l._afunc.reset(ActivationFunc<DType>::create(aft));
            _layers.push_back(l);

            const unsigned int wrows = nodes_per_layer[i+1];
            const unsigned int wcols = nodes_per_layer[i] + 1; // +1 is from const term
            Matrix<DType> wm(wrows, wcols);
            _weights.push_back(wm);
        }
        // for the last layer, just add the nodes
        Layer l;
        l.resize(nodes_per_layer.back());
        l._afunc.reset(ActivationFunc<DType>::create(aft));
        _layers.push_back(l);
    }

    //! propagate inputs forward
    template <class DType>
    const std::vector<DType>&
    NNetFeedForward<DType>::propagate_forward(const std::vector<DType>& inputs)
    {
        // set first layer
        auto nlayers = _layers.size();
        if (nlayers == 0)
            throw std::exception("No layers");

        auto nnodes = _layers[0]._out_vals.size();
        if (nnodes != inputs.size())
            throw std::exception("Inputs size mismatch");

        // set initial values
        _layers[0]._out_vals.assign(inputs.begin(), inputs.end());
        for (auto l = 0; l <= nlayers-2; ++l)
        {
            //            _layers[l+1]._in_
        }

        
        return _layers.back()._out_vals;        
    }

    
    
};

#endif
