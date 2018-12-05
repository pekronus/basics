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
        //! default ctor
        NNetFeedForward();;
        
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

        //! add a layer
        void add_layer(const int nnodes, const ActivationFunc<DType>* af) override;
        //! propagate forward
        const std::vector<DType>& propagate_forward(const std::vector<DType>& inputs);
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
        //! layers
        std::vector<Layer> _layers;
        //! weights (layer/ node-to / node-from (last one is the bias)) 
        std::vector< std::vector< std::vector<DType> > > _weights;
    };

    //! add a layer
    template <class DType>
    void
    NNetFeedForward<DType>::add_layer(const int nnodes,
                                      const ActivationFunc<DType>* af)
    {
        Layer l;
        l.resize(nnodes);
        l._afunc.reset(af);
        _layers.push_back(l);
        
        // add weights matrix if more than one layer
        auto lsz = _layers.size();
        if (lsz <= 1)
            return;
        
        std::vector< std::vector<DType> > wm;
        wm.resize(nnodes);
        for (int i = 0; i < nnodes; ++i)
            wm[i].assign(_layers[lsz-2]._out_vals.size() + 1, 0.0);
        
        _weights.push_back(wm);
    
    }
    
    //! ctor
    template <class DType>
    NNetFeedForward<DType>::NNetFeedForward()
    {
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
        // for (int 
        
        return _layers.back._out_vals;        
    }

    
    
};

#endif
