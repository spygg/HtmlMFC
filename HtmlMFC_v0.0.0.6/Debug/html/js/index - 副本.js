var cpp_object = null;

function HelloAlert(value){
	alert(value);
    //window.external.CloseWindow();
}


function SetCppObject(obj) {
    cpp_object = obj;
}


function CloseWindow(){
    if (cpp_object != null) {
        cpp_object.CloseWindow();
    }
}

function MinWindow(){
    if (cpp_object != null) {
        cpp_object.MinWindow();
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

