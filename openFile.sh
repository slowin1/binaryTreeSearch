chmod +x BinaryTree.txt
FILE="BinaryTree.txt"
xed "$FILE" &
sleep 2
PID=$!
wait $PID
