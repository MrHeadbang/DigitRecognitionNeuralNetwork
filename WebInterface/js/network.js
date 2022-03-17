function sigmoid(value) {
    return 1 / (1 + Math.pow(2.71828182845904, -value));
}
function calcLayerNeurons(layerInput, layerWeights) {
    var outputNeurons = [];
    for (var i = 0; i < layerWeights.length; i++) {
        var currentWeights = layerWeights[i];
        //Bias value 1
        var outputNeuron = 1;
        for (var j = 0; j < currentWeights.length; j++) {
            outputNeuron += currentWeights[j] * layerInput[j];
        }
        outputNeurons.push(sigmoid(outputNeuron));
    }
    return outputNeurons;
}

function feedForward(input) {        
    for (var i = 0; i < data.length; i++) {
        var currentWeights = data[i];
        input = calcLayerNeurons(input, currentWeights);
    }
    return input;
}    
