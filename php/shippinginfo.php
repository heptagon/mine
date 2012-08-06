<?php
echo "begin";

$clientID='EMV0KUTqXE6SJm5efZuWyyBQegJNEpDVcvOkcPzxpr9p';
$secret='ELaEnsJ7Adb8jlr8TStBouClmxIQ7RVI9lJOMN_qaBpNradPzahXO2iRZBr8qZuEFA';
$txnid='1121';
$payload=array();
$payload['Client']=$clientID;
$payload['Secret']=$secret;
$payload['CheckoutTransactionId']=$txnid;
$jarr=json_encode($payload);

                        $fields=array(
                                'payload'   => $jarr
                                );
                        $poststr="";
                        print_r($fields);
                        foreach ( $fields as $key => $value) { $poststr.=$key.'='.$value.'&'; }
                        $url="https://D-SJC-00531130.corp.ebay.com/xii-gadget-server/resources/merchantcheckout/shippinginfo";
                        $csession=curl_init();
                        curl_setopt($csession,CURLOPT_RETURNTRANSFER,true);
                        curl_setopt($csession,CURLOPT_URL,$url);
                        curl_setopt($csession,CURLOPT_POST,count($fields));
                        curl_setopt($csession,CURLOPT_POSTFIELDS,$poststr);
                        $resp=curl_exec($csession);
                        echo $resp;

                        $resparr=json_decode($resp,true);
                        var_dump($resparr);

                        curl_close($csession);
echo "done";




?>
