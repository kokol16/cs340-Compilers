function(){}
function(x1 ,x2 ){
    local x;
    local y;
}
function(){}

function f(x3 ) {
    local f= 10;
    function h(x6,x65,x67) { 
        return f;       // error
        return ::f(); 
    }
}