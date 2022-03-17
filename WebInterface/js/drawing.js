const container = document.querySelector('.class-drawing-container');
const clearDiv = document.querySelector('.class-drawing-clear');
const pixelScaleArea = document.querySelector('.class-drawing-float-result');
var resultTable = document.querySelector('.class-result-table');

function reset(){
    container.innerHTML = '';
    pixelScaleArea.value = '';
    resultTable.innerHTML = '';
    for (var resultRows = 0; resultRows < 10; resultRows++) {
        resultTable.innerHTML += '<tr>';
        resultTable.innerHTML += '<td>0 - 0</td>';
        resultTable.innerHTML += '</tr>';
    }
    populate(28);
}
clearDiv.addEventListener('click', reset);

function disableSelection(target){

    if (typeof target.onselectstart!="undefined") //IE route
        target.onselectstart=function(){return false}

    else if (typeof target.style.MozUserSelect!="undefined") //Firefox route
        target.style.MozUserSelect="none"

    else //All other route (ie: Opera)
        target.onmousedown=function(){return false}

    target.style.cursor = "default"
}
disableSelection(container);

let draw = false;

function populate(size) {
  container.style.setProperty('--size', size);
  for (let i = 0; i < size * size; i++) {
    const div = document.createElement('div');
    div.classList.add('pixel');
    div.addEventListener('mouseover', function(){
        if(!draw) return
        div.style.backgroundColor = "#ffffff";
        refreshPixels();
    });
    div.addEventListener('mousdown', function(){
        div.style.backgroundColor = "#ffffff";
    });

    container.appendChild(div);
  }
}

window.addEventListener("mousedown", function(){
    draw = true;
});

window.addEventListener("mouseup", function(){
    draw = false;
});

populate(28);
reset();



function indexOfMax(arr) {
    if (arr.length === 0) {
        return -1;
    }

    var max = arr[0];
    var maxIndex = 0;

    for (var i = 1; i < arr.length; i++) {
        if (arr[i] > max) {
            maxIndex = i;
            max = arr[i];
        }
    }

    return maxIndex;
}

function refreshPixels() {
    var containerPixels = container.innerHTML;
    var pixelScale = containerPixels.split('</div>');
    var pixelScaleFloats = [];
    
    for (var i = 0; i < pixelScale.length - 1; i++) {
        var element = pixelScale[i];
        if (element == '<div class="pixel">') {
            pixelScaleFloats.push(1);
        } else {
            pixelScaleFloats.push(0);
        }
    }
    pixelScaleArea.value = pixelScaleFloats;
    
    var output = feedForward(pixelScaleFloats);
    refreshTable(output);
}


function refreshTable(output) {
    resultTable.innerHTML = '';
    var maxValue = indexOfMax(output);
    for (var resultRows = 0; resultRows < 10; resultRows++) {
        resultTable.innerHTML += '<tr>';
        
        var color;
        if (resultRows == maxValue) {
            color = "#FFAA01";
        } else {
            color = "#FFFFFF";
        }
        resultTable.innerHTML += '<td><font style="color: ' + color + ';">' + resultRows + '</font> - <font style="color: ' + color + ';">' + parseFloat(output[resultRows].toFixed(5)) + '</font></td>';
        resultTable.innerHTML += '</tr>';
    }
    
}