#include <ml/NNetFeedForward.hpp>
#include <iostream>

using namespace pekronus;

int
main(int argc, char** argv)
{
    std::vector<unsigned int> nodes_per_layer{2,2,2};
    NNetFeedForward<float> nnff(nodes_per_layer, ActivationFuncType::Sigmoid);

    WeightsMatrix<float> w(2,3, 1.0);
    std::vector< WeightsMatrix<float> > weights;
    weights.push_back(w);
    weights.push_back(w);
    weights.push_back(w);
    
    nnff.set_weights(weights);

    
    std::vector<float> out = nnff.propagate_forward({1.0, 2.0});
    std::cout << out[0] << '\t' << out[1] << std::endl;
}
