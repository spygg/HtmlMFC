var cpp_object = null;

function SetCppObject(obj) {
        cpp_object = obj;
}

function HelloAlert(value){
	alert(value);
    //window.external.CloseWindow();
}




function CloseWindow(){
    if (cpp_object != null) {
        cpp_object.CloseWindow();
    }
    else{
        alert('not init!');
    }
}

function MinWindow(){
    if (cpp_object != null) {
        cpp_object.MinWindow();
    }    else{
        alert('not init!');
    }
}

function MaxWindow(){
    if (cpp_object != null) {
        cpp_object.MaxWindow();
    }
}


function MoveWindowPos(e){
    var x = e.clientX;
    var y = e.clientY;
   
    
    if (cpp_object != null) {
        cpp_object.MoveWindowPos(x.toString(), y.toString());
    }
}


