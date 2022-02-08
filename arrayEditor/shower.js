const rgbToHex = (r, g, b) => '#' + [r, g, b].map(x => {
    const hex = x.toString(16)
    return hex.length === 1 ? '0' + hex : hex
  }).join('')

function createPixel(scale) {
    scale = Math.round(scale);
    var grayscale = rgbToHex(scale, scale, scale);
    
    var code = '<div style="display: inline-block; background-color: ' + grayscale + '; width: 20px; height: 20px; border: solid 3px #FFAA01;"> <text style="font-size: 0px;">' + grayscale + '</text></div>';
    document.getElementById("builder").innerHTML += code;
}

function show() {
    var fieldText = document.getElementById("ta").value;
    var array = [0];
    mainarray = (fieldText.split(" ").map(Number));
    array.push.apply(array, mainarray);
    array = array.map(function(x) { return x * 255; });
    for (let i = 0; i < array.length; i++) {
        createPixel(array[i]);
        if(i % 28 == 0)
        document.getElementById("builder").innerHTML += '<br>';
    }
}