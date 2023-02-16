using Random
using Primes
using Plots



function densityOfPrimes(n::UInt128,t::UInt128,amountOfTests::UInt128)
    pow2 = BigInt(1)
    while pow2 < 2*t+1
        pow2 = 2*pow2
    end
    ans = 0
    for i in 1:amountOfTests
        candidate = rand((1+t):((n+t)^3))
        candidate = candidate * pow2 + 1
        if(isprime(candidate)) 
            ans = ans + 1
        end
    end
    return ans/amountOfTests*((n+t)^3 - (t+1)+1)/((n+t)*(n+t))
end
t = zeros(30)
n = zeros(30)
z = zeros(30,30)

for i in 1:30
	t[i] = i
	n[i] = i
	for j in 1:30
		println(i," ",j)
		z[i,j]=densityOfPrimes(UInt128(2)^i,UInt128(2)^j,UInt128(1000000))	
	end
end
for i in 1:30
    for j in 1:30
        z[i,j]=log(2,z[i,j])
    end
end
Plots.heatmap(t,n,z,xlabel="log(t)",ylabel="log(n)")
Plots.savefig("wykres.png")
