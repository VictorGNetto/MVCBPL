function f100
def
enddef
return ci0
end

function f101 pi1
def
enddef
return ci0
end

function f102 pa1, pi2
def
enddef
return ci0
end

function f103 pa1, pi2, pa3
def
enddef
return ci0
end

function f1
def
var vi1
enddef
vi1 = call f100
return ci0
end

function f2
def
var vi1
enddef
vi1 = call f101 vi1
return ci0
end

function f3 pa1
def
var vi1
vet 
enddef
vi1 = call f102 pa1 ci-5
return ci0
end

function f4 pa1, pi2
def
var vi1
vet va2 size ci5
vet 
enddef
vi1 = call f103 pa1 pi2 va2
return ci0
end