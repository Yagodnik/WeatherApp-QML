WorkerScript.onMessage = function(msg) {
    console.log(msg.index,msg.prstate);
    msg.model.append({ name: "Test!" });

    msg.model.sync();
 }
