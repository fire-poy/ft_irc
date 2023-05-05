#!/bin/bash
endline="\r\n"
LF="$'\n'"
machine="127.0.0.1"
## ATENTION: Test requirements
#	For the test to work correctly, the following line in the pass.cpp file must be commented out
#		sendReply(3, ctime(_server->getStartTime()), "", "", "");

input="NICK Almodovar${endline}USER pedro pedro localhost :Pedro Almodovar${endline}PASS asd$endline"
# input+="QUITqhola$endline mas mierda$endline"
# input+="QUIT #usa 	$endline mas mierda"
# input+="QUIT #iaosa 	$endline mas mierda $endline"
input+="QUIT :#s :ok sok ko,iaosdsa 	$endline mas mierda"
# input+=QUIT
# input+=QUIT
# input+=QUIT
# input+=QUIT
# input+=QUIT
# ipServ=$( ping -c 1 $machine | grep "from" | awk '{print $4}' | sed 's/.$//')

# echo -ne "$input" | nc -C ${ipServ} 6667
echo -ne "$input" | nc -C localhost 6667

# inputs=("$input1" "$input2" "$input3" "$input4" "$input5"
# 		"$input6" "$input7" "$input8" "$input9" "$input10"
# 		"$input11" "$input12" "$input13" "$input14" "$input15"
# 		"$input99")

# expected_outputs=("$expected_output1" "$expected_output2" "$expected_output3"
# 				"$expected_output4" "$expected_output5" "$expected_output6" "$expected_output7"
# 				"$expected_output8" "$expected_output9" "$expected_output10" "$expected_output11"
# 				"$expected_output12" "$expected_output13" "$expected_output14" "$expected_output15"
# 				"$expected_output99")

# for i in "${!inputs[@]}"
# do
#     input="${inputs[$i]}"
#     expected_output="${expected_outputs[$i]}"

# 	echo -ne "\033[1;37mSTART TEST $((i+1))\033[0m\n"

#     output=$(echo -ne "$input" | nc -C ${ipServ} 6667)

# 	#####		UNCOMMENT TO ADD NEW TESTS		#####
# 	# printf "\n"
# 	# printf "    EXPECTED output: %s" "${expected_output}" | cat -e
# 	# printf "\n"
# 	# printf "\n"
# 	# printf "    REAL output: %s" "${output}" | cat -e
# 	# printf "\n"

#     if [[ "$output" == "$expected_output" ]]; then
#         # echo -ne "${input}"
# 		echo -e "\033[1;32mTEST $((i+1)): OK\033[0m\n"
#     else
#         # echo -ne "${input}"
#         echo -e "\033[1;31mKO\033[0m"
# 		printf "\n"

#     fi
# done

