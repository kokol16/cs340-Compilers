function f() {
    local f= 10;
    function h() { 
        return f;       // error
        return ::f(); 
    }
}